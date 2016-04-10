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
        aepBoolValue    m_bool;
        aepIntValue     m_int;
        aepDoubleValue  m_double;
        aepPoint2DValue m_point2d;
        aepPoint3DValue m_point3d;
        aepColorValue   m_color;
        aepLayerValue   m_layer;
    };

    PF_ParamDef m_pf;
};

#endif // aepParam_h
