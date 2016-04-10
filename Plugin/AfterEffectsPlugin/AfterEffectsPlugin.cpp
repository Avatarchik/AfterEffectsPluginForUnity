#include "pch.h"
#include "Foundation.h"
#include "AfterEffectsPlugin.h"
#include "aepInstance.h"
#include "aepModule.h"

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

aepCLinkage aepExport void aepRender(aepModule *mod)
{
    // todo
}

