#ifndef aepParam_h
#define aepParam_h

class aepParam
{
public:
    aepParam();
    ~aepParam();

    const aepParamInfo& getInfo() const;
    void*               getDataPtr();
    void                getValue(void *dst);
    void                setValue(const void *src);

private:
    aepParamInfo m_info;
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
