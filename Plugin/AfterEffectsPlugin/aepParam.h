#ifndef aepParam_h
#define aepParam_h

class aepParam
{
public:
    aepParam(aepInstance *inst);
    ~aepParam();

    const std::string&  getName() const;
    aepParamType        getType() const;

    void*               getDataPtr();
    void                getValue(void *dst);
    void                setValue(const void *src);

    void                apply();

private:
    aepInstance *m_inst;
    std::string m_name;
    aepParamType m_type;
    union {
        aepBoolValue    m_bool;
        aepFloatValue   m_float;
        aepPoint2DValue m_point2d;
        aepPoint3DValue m_point3d;
        aepColorValue   m_color;
        aepLayerValue   m_layer;
    };
};

#endif // aepParam_h
