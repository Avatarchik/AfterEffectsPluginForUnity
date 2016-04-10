#ifndef AfterEffectsPlugin_h
#define AfterEffectsPlugin_h

#define aepCLinkage extern "C"
#ifdef _WIN32
    #ifndef aepStaticLink
        #ifdef aepImpl
            #define aepExport __declspec(dllexport)
        #else
            #define aepExport __declspec(dllimport)
        #endif
    #else
        #define aepExport
    #endif
#else
    #define aepExport
#endif

class aepModule;
class aepInstance;
class aepParam;


struct aepPoint2D
{
    int x, y;
    aepPoint2D() : x(), y() {}
    aepPoint2D(int _x, int _y) : x(_x), y(_y) {}
};
struct aepPoint3D
{
    double x, y, z;
    aepPoint3D() : x(), y(), z() {}
    aepPoint3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
};
struct aepColor
{
    unsigned char r, g, b, a;
    aepColor() : r(), g(), b(), a() {}
    aepColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) : r(_r), g(_g), b(_b), a(_a) {}
};
struct aepLayer
{
    void *pixels;
    int width, height, rowbytes;

    aepLayer() : pixels(), width(), height(), rowbytes() {}
    aepLayer(void *p, int w, int h, int r) : pixels(p), width(w), height(h), rowbytes(r) {}
};


enum aepParamType
{
    aepParamType_Unknown,
    aepParamType_Bool,
    aepParamType_Float,
    aepParamType_Point2D,
    aepParamType_Point3D,
    aepParamType_Color,
    aepParamType_Path,
    aepParamType_Layer,
};

struct aepParamInfo
{
    const char *name;
    aepParamType type;
};

struct aepBoolValue
{
    bool value, def;
};
struct aepIntValue
{
    int value, def, min, max;
};
struct aepPoint2DValue
{
    aepPoint2D value, def;
};
struct aepPoint3DValue
{
    aepPoint3D value, def;
};
struct aepColorValue
{
    aepColor value, def;
};
struct aepLayerValue
{
    aepLayer value;
};


aepCLinkage aepExport aepModule*    aepLoadModule(const char *path);
aepCLinkage aepExport void          aepUnloadModule(aepModule *mod);
aepCLinkage aepExport aepInstance*  aepCreateInstance(aepModule *mod);
aepCLinkage aepExport void          aepDestroyInstance(aepInstance *ins);

aepCLinkage aepExport int           aepGetNumParams(aepInstance *ins);
aepCLinkage aepExport aepParam*     aepGetParam(aepInstance *ins, int i);
aepCLinkage aepExport aepParam*     aepGetParamByName(aepInstance *ins, const char *name);
aepCLinkage aepExport void          aepGetParamInfo(aepParam *param, aepParamInfo *dst);
aepCLinkage aepExport void          aepGetParamValue(aepParam *param, void *value);
aepCLinkage aepExport void          aepSetParamValue(aepParam *param, const void *value);

aepCLinkage aepExport void          aepRender(aepInstance *ins, aepLayer *dst);

#endif // AfterEffectsPlugin_h
