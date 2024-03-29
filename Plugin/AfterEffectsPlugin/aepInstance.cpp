#include "pch.h"
#include "aepInternal.h"


aepInstance::aepInstance(aepModule *mod)
    : m_module(mod)
    , m_entrypoint(mod->getEntryPoint())
{
    memset(&m_pf_in, 0, sizeof(m_pf_out));
    memset(&m_pf_out, 0, sizeof(m_pf_in));

    (void*&)m_pf_in.effect_ref = this;
    m_pf_in.inter = aepGetHostCallbacks();
    m_pf_in.utils = &aepGetUtilCallbacks();
    m_pf_in.pica_basicP = &aepGetSPBasicSuite();

    {
        PF_ParamDef def;
        memset(&def, 0, sizeof(def));
        strcpy(def.name, "Input");
        def.param_type = PF_Param_LAYER;
        addParam(0, def);
    }

    callPF(PF_Cmd_GLOBAL_SETUP);
    callPF(PF_Cmd_PARAMS_SETUP);
}

aepInstance::~aepInstance()
{
    callPF(PF_Cmd_GLOBAL_SETDOWN);
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
        if (!p) { continue; }
        if (strcmp(p->getName(), name) == 0) {
            return p.get();
        }
    }
    return nullptr;
}

void aepInstance::setInput(aepLayer *inp)
{
    getParam(0)->setValue(&inp);
}

aepLayer* aepInstance::render(double time, int width, int height)
{
    m_output.resize(width, height);

    callPF(PF_Cmd_FRAME_SETUP);
    callPF(PF_Cmd_RENDER);
    callPF(PF_Cmd_FRAME_SETDOWN);
    return &m_output;
}

void aepInstance::callPF(int cmd)
{
    m_entrypoint(cmd, &m_pf_in, &m_pf_out, &m_pf_params[0], &m_output.m_pf, this);
}

aepParam* aepInstance::addParam(int pos, const PF_ParamDef& pf)
{
    auto *param = new aepParam(this, pf);

    // pos < 0 means append to back
    if (pos < 0) {
        pos = (int)m_params.size();
        m_params.emplace_back(aepParamPtr(param));
    }
    else {
        if (pos >= (int)m_params.size()) {
            m_params.resize((size_t)pos + 1);
        }
        m_params[pos] = aepParamPtr(param);
    }

    m_pf_params.resize(m_params.size());
    m_pf_params[pos] = &param->getPFParam();
    return param;
}
