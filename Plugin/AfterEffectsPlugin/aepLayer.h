#ifndef aepLayer_h
#define aepLayer_h

class aepLayer
{
public:
    aepLayer();

    PF_LayerDef&    getPF();
    aepImageRGBAu8& getImage();

    int     getWidth() const;
    int     getHeight() const;
    int     getPitch() const;
    void*   getData();

    void    resize(int w, int h);

public:
    PF_LayerDef m_pf;
    aepImageRGBAu8 m_image;
};

#endif // aepLayer_h
