#include "pch.h"
#include "Foundation.h"
#include "AfterEffectsPlugin.h"
#include "aepModule.h"
#include "aepInstance.h"
#include "aepParam.h"


aepInstance::aepInstance(aepModule *mod)
    : m_module(mod)
    , m_entrypoint(mod->getEntryPoint())
{
}

aepInstance::~aepInstance()
{
}

int aepInstance::getNumParams() const
{
    return (int)m_params.size();
}

aepParam* aepInstance::getParam(int i)
{
    return m_params[i].get();
}

aepParam* aepInstance::getParamByName(const char *name)
{
    for(auto& p : m_params) {
        if (p->getName() == name) {
            return p.get();
        }
    }
    return nullptr;
}

void aepInstance::render()
{
    for (auto& p : m_params) { p->apply(); }

    //m_entrypoint(PF_Cmd_FRAME_SETUP);
    //m_entrypoint(PF_Cmd_RENDER);
    //m_entrypoint(PF_Cmd_FRAME_SETDOWN);
}
