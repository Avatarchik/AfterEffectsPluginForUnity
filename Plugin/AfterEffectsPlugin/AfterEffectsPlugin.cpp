#include "pch.h"
#include "aepInternal.h"


aepCLinkage aepExport aepLayer* aepCreateLayer()
{
    return new aepLayer();
}
aepCLinkage aepExport void aepDestroyLayer(aepLayer *layer)
{
    delete layer;
}
aepCLinkage aepExport void aepResizeLayer(aepLayer *layer, int width, int height)
{
    if (!layer) { return; }
    layer->resize(width, height);
}
aepCLinkage aepExport void aepGetLayerData(aepLayer *layer, aepLayerData *dst)
{
    if (!layer || !dst) { return; }
    dst->width      = layer->getWidth();
    dst->height     = layer->getHeight();
    dst->rowbytes   = layer->getPitch();
    dst->pixels     = layer->getData();
}

namespace {
    typedef std::unique_ptr<aepModule> aepModulePtr;
    std::map<std::string, aepModulePtr> g_modules;
}

aepCLinkage aepExport aepModule* aepLoadModule(const char *path)
{
    // if already loaded, return it
    auto i = g_modules.find(path);
    if (i != g_modules.end()) {
        return i->second.get();
    }

    auto ret = new aepModule();
    if (!ret->load(path)) {
        delete ret;
        return false;
    }
    g_modules[path] = aepModulePtr(ret);
    return ret;
}

aepCLinkage aepExport void aepUnloadModule(aepModule *mod)
{
    // do nothing
}


aepCLinkage aepExport aepInstance*  aepCreateInstance(aepModule *mod)
{
    if (!mod) { return nullptr; }
    return mod->createInstance();
}

aepCLinkage aepExport void aepDestroyInstance(aepInstance *ins)
{
    delete ins;
}

aepCLinkage aepExport int aepGetNumParams(aepInstance *ins)
{
    if (!ins) { return 0; }
    return ins->getNumParams();
}
aepCLinkage aepExport aepParam* aepGetParam(aepInstance *ins, int i)
{
    if (!ins) { return nullptr; }
    return ins->getParam(i);
}
aepCLinkage aepExport aepParam* aepGetParamByName(aepInstance *ins, const char *name)
{
    if (!ins) { return nullptr; }
    return ins->getParamByName(name);
}

aepCLinkage aepExport void aepGetParamInfo(aepParam *param, aepParamInfo *dst)
{
    if (!param || !dst) { return; }
    dst->name = param->getName();
    dst->type = param->getType();
}
aepCLinkage aepExport void aepGetParamValue(aepParam *param, void *value)
{
    if (!param || !value) { return; }
    param->getValue(value);
}
aepCLinkage aepExport void aepSetParamValue(aepParam *param, const void *value)
{
    if (!param || !value) { return; }
    param->setValue(value);
}

aepCLinkage aepExport void aepSetInput(aepInstance *ins, aepLayer *layer)
{
    if (!ins) { return; }
    ins->setInput(layer);
}

aepCLinkage aepExport aepLayer* aepRender(aepInstance *ins, double time, int width, int height)
{
    if (!ins) { return nullptr; }
    return ins->render(time, width, height);
}

