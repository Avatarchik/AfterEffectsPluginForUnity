#include "pch.h"
#include "aepInternal.h"

aepLayer::aepLayer()
{
    memset(&m_pf, 0, sizeof(m_pf));
    m_pf.world_flags |= PF_WorldFlag_WRITEABLE;
    m_pf.pix_aspect_ratio.num = 1;
    m_pf.pix_aspect_ratio.den = 1;
    m_pf.dephault = PF_LayerDefault_NONE;
}

PF_LayerDef&    aepLayer::getPF() { return m_pf; }
aepImageRGBAu8& aepLayer::getImage() { return m_image; }
int             aepLayer::getWidth() const { return m_image.getWidth(); }
int             aepLayer::getHeight() const { return m_image.getHeight(); }
int             aepLayer::getPitch() const { return m_image.getPitch(); }
void*           aepLayer::getData() { return m_image.getData(); }


void aepLayer::resize(int w, int h)
{
    m_image.resize(w, h);
    m_pf.width = m_image.getWidth();
    m_pf.height = m_image.getHeight();
    m_pf.rowbytes = m_image.getPitch();
    m_pf.data = (PF_PixelPtr)m_image.getData();
}
