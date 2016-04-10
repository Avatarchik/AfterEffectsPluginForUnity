#ifndef aepParam_h
#define aepParam_h

class aepParam
{
public:
    aepParam(aepInstance *inst);
    ~aepParam();
    void                setup();

    const char*         getName() const;
    aepParamType        getType() const;

    void*               getDataPtr();
    void                getValue(void *dst);
    void                setValue(const void *src);

    void                apply();

public:
    // internal
    PF_ParamDef&        getPFParamDef();
    void                copyToPF();
    void                copyFromPF();

private:
    aepInstance *m_inst;
    aepParamType m_type;
    union {
        aepBoolValue    m_bool;
        aepIntValue   m_int;
        aepPoint2DValue m_point2d;
        aepPoint3DValue m_point3d;
        aepColorValue   m_color;
        aepLayerValue   m_layer;
    };

    PF_ParamDef m_pf;
};

#endif // aepParam_h
