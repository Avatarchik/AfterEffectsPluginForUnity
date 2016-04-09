﻿#include "pch.h"

#ifdef utjSupportD3D11
#include "Foundation.h"
#include "GraphicsDevice.h"
#include <d3d11.h>
const int D3D11MaxStagingTextures = 32;

namespace utj {
class GraphicsDeviceD3D11 : public GraphicsDevice
{
public:
    GraphicsDeviceD3D11(void *device);
    ~GraphicsDeviceD3D11();
    void* getDevicePtr() override;
    GfxDeviceType getDeviceType() override;
    void sync() override;
    bool readTexture(void *o_buf, size_t bufsize, void *tex, int width, int height, PixelFormat format) override;
    bool writeTexture(void *o_tex, int width, int height, PixelFormat format, const void *buf, size_t bufsize) override;

private:
    void clearStagingTextures();
    ID3D11Texture2D* findOrCreateStagingTexture(int width, int height, PixelFormat format);

private:
    ID3D11Device *m_device;
    ID3D11DeviceContext *m_context;
    ID3D11Query *m_query_event;
    std::map<uint64_t, ID3D11Texture2D*> m_staging_textures;
};


GraphicsDevice* CreateGraphicsDeviceD3D11(void *device)
{
    return new GraphicsDeviceD3D11(device);
}

GraphicsDeviceD3D11::GraphicsDeviceD3D11(void *device)
    : m_device((ID3D11Device*)device)
    , m_context(nullptr)
    , m_query_event(nullptr)
{
    clearStagingTextures();
    if (m_device != nullptr)
    {
        m_device->GetImmediateContext(&m_context);

        D3D11_QUERY_DESC qdesc = {D3D11_QUERY_EVENT , 0};
        m_device->CreateQuery(&qdesc, &m_query_event);
    }
}

GraphicsDeviceD3D11::~GraphicsDeviceD3D11()
{
    if (m_context != nullptr)
    {
        m_context->Release();
        m_context = nullptr;

        m_query_event->Release();
        m_query_event = nullptr;
    }
}

void* GraphicsDeviceD3D11::getDevicePtr() { return m_device; }
GfxDeviceType GraphicsDeviceD3D11::getDeviceType() { return GfxDeviceType_D3D11; }


static DXGI_FORMAT GetInternalFormatD3D11(PixelFormat fmt)
{
    switch (fmt)
    {
    case PixelFormat_RGBAu8:  return DXGI_FORMAT_R8G8B8A8_TYPELESS;

    case PixelFormat_RGBAf16: return DXGI_FORMAT_R16G16B16A16_FLOAT;
    case PixelFormat_RGf16:   return DXGI_FORMAT_R16G16_FLOAT;
    case PixelFormat_Rf16:    return DXGI_FORMAT_R16_FLOAT;

    case PixelFormat_RGBAf32: return DXGI_FORMAT_R32G32B32A32_FLOAT;
    case PixelFormat_RGf32:   return DXGI_FORMAT_R32G32_FLOAT;
    case PixelFormat_Rf32:    return DXGI_FORMAT_R32_FLOAT;

    case PixelFormat_RGBAi32: return DXGI_FORMAT_R32G32B32A32_SINT;
    case PixelFormat_RGi32:   return DXGI_FORMAT_R32G32_SINT;
    case PixelFormat_Ri32:    return DXGI_FORMAT_R32_SINT;
    }
    return DXGI_FORMAT_UNKNOWN;
}


ID3D11Texture2D* GraphicsDeviceD3D11::findOrCreateStagingTexture(int width, int height, PixelFormat format)
{
    if (m_staging_textures.size() >= D3D11MaxStagingTextures) {
        clearStagingTextures();
    }

    DXGI_FORMAT internal_format = GetInternalFormatD3D11(format);
    uint64_t hash = width + (height << 16) + ((uint64_t)internal_format << 32);
    {
        auto it = m_staging_textures.find(hash);
        if (it != m_staging_textures.end())
        {
            return it->second;
        }
    }

    D3D11_TEXTURE2D_DESC desc = {
        (UINT)width, (UINT)height, 1, 1, internal_format, { 1, 0 },
        D3D11_USAGE_STAGING, 0, D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE, 0
    };
    ID3D11Texture2D *ret = nullptr;
    HRESULT hr = m_device->CreateTexture2D(&desc, nullptr, &ret);
    if (SUCCEEDED(hr))
    {
        m_staging_textures.insert(std::make_pair(hash, ret));
    }
    return ret;
}

void GraphicsDeviceD3D11::clearStagingTextures()
{
    for (auto& pair : m_staging_textures)
    {
        pair.second->Release();
    }
    m_staging_textures.clear();
}

void GraphicsDeviceD3D11::sync()
{
    m_context->End(m_query_event);
    while (m_context->GetData(m_query_event, nullptr, 0, 0) == S_FALSE) {
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}

bool GraphicsDeviceD3D11::readTexture(void *o_buf, size_t bufsize, void *tex_, int width, int height, PixelFormat format)
{
    if (m_context == nullptr || tex_ == nullptr) { return false; }
    int psize = GetPixelSize(format);

    // Unity の D3D11 の RenderTexture の内容は CPU からはアクセス不可能になっている。
    // なので staging texture を用意してそれに内容を移し、CPU はそれ経由でデータを読む。
    ID3D11Texture2D *tex = (ID3D11Texture2D*)tex_;
    ID3D11Texture2D *tmp = findOrCreateStagingTexture(width, height, format);
    m_context->CopyResource(tmp, tex);

    // ID3D11DeviceContext::Map() はその時点までのコマンドの終了を待ってくれないっぽくて、
    // ↑の CopyResource() が終わるのを手動で待たないといけない。
    sync();

    D3D11_MAPPED_SUBRESOURCE mapped = { 0 };
    HRESULT hr = m_context->Map(tmp, 0, D3D11_MAP_READ, 0, &mapped);
    if (SUCCEEDED(hr))
    {
        char *wpixels = (char*)o_buf;
        int wpitch = width * GetPixelSize(format);
        const char *rpixels = (const char*)mapped.pData;
        int rpitch = mapped.RowPitch;

        // 表向きの解像度と内部解像度は一致しないことがあるようで、その場合 1 ラインづつコピーする必要がある。
        // (手元の環境では内部解像度は 32 の倍数になるっぽく見える)
        if (wpitch == rpitch)
        {
            memcpy(wpixels, rpixels, bufsize);
        }
        else
        {
            for (int i = 0; i < height; ++i)
            {
                memcpy(wpixels, rpixels, wpitch);
                wpixels += wpitch;
                rpixels += rpitch;
            }
        }

        m_context->Unmap(tmp, 0);
        return true;
    }
    return false;
}

bool GraphicsDeviceD3D11::writeTexture(void *o_tex, int width, int height, PixelFormat format, const void *buf, size_t bufsize)
{
    int psize = GetPixelSize(format);
    int pitch = psize * width;
    const size_t num_pixels = bufsize / psize;

    D3D11_BOX box;
    box.left = 0;
    box.right = width;
    box.top = 0;
    box.bottom = ceildiv((UINT)num_pixels, (UINT)width);
    box.front = 0;
    box.back = 1;
    ID3D11Texture2D *tex = (ID3D11Texture2D*)o_tex;
    m_context->UpdateSubresource(tex, 0, &box, buf, pitch, 0);
    return true;
}

} // namespace utj
#endif // utjSupportD3D11
