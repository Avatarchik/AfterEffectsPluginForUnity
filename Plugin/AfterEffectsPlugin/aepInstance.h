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

private:
    typedef std::unique_ptr<aepParam> aepParamPtr;

    aepModule *m_module;
    aepEntryPoint m_entrypoint;
    std::vector<aepParamPtr> m_params;
};

#endif // aepInstance_h
