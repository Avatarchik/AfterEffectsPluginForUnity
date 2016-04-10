#ifndef aepInstance_h
#define aepInstance_h

class aepInstance
{
public:
    aepInstance(aepModule *mod);
    ~aepInstance();

    int         getNumParams() const;
    aepParam*   getParam(int i);
    aepParam*   getParamByName(const char *name);

    void        render();

public:
    // internal
    aepParam*   addParam(int pos, const PF_ParamDef& pf);
    void        callPF(int cmd);

private:
    typedef std::unique_ptr<aepParam>   aepParamPtr;
    typedef std::vector<aepParamPtr>    aepParams;
    typedef std::vector<PF_ParamDef*>   PF_ParamDefs;

    aepModule       *m_module;
    aepEntryPoint   m_entrypoint;
    aepParams       m_params;

    PF_InData       m_pf_in;
    PF_OutData      m_pf_out;
    PF_ParamDefs    m_pf_params;
    PF_LayerDef     m_pf_output;
};

#endif // aepInstance_h
