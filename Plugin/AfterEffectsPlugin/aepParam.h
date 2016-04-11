#ifndef aepParam_h
#define aepParam_h

class aepParam
{
public:
    aepParam(aepInstance *inst, const PF_ParamDef& pf);
    ~aepParam();

    const char*         getName() const;
    aepParamType        getType() const;

    void*               getDataPtr();
    void                getValue(void *dst);
    void                setValue(const void *src);

public:
    // internal
    PF_ParamDef&        getPFParam();
    void                setup(const PF_ParamDef& def);

private:
    aepInstance *m_inst;
    aepParamType m_type;
    union {
        aepBoolParamValue    vbool;
        aepIntParamValue     vint;
        aepDoubleParamValue  vdouble;
        aepPoint2DParamValue vpoint2d;
        aepPoint3DParamValue vpoint3d;
        aepColorParamValue   vcolor;
        aepLayerParamValue   vlayer;
    } m_data;

    PF_ParamDef m_pf;
};

#endif // aepParam_h
