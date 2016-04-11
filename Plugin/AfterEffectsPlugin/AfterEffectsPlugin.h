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

class aepLayer;
class aepModule;
class aepInstance;
class aepParam;


struct aepPoint2D
{
    int x, y;
};
struct aepPoint3D
{
    double x, y, z;
};
struct aepColor
{
    unsigned char a, r, g, b;
};
struct aepLayerData
{
    void *pixels;
    int width, height, rowbytes;
};


enum aepParamType
{
    aepParamType_Unknown,
    aepParamType_Bool,
    aepParamType_Int,
    aepParamType_Double,
    aepParamType_Point2D,
    aepParamType_Point3D,
    aepParamType_Color,
    aepParamType_Layer,
    aepParamType_Path, // not supported yet
};

struct aepParamInfo
{
    const char *name;
    aepParamType type;
};

struct aepBoolParamValue
{
    bool value, def;
};
struct aepIntParamValue
{
    int value, def, min, max;
};
struct aepDoubleParamValue
{
    double value, def, min, max;
};
struct aepPoint2DParamValue
{
    aepPoint2D value, def;
};
struct aepPoint3DParamValue
{
    aepPoint3D value, def;
};
struct aepColorParamValue
{
    aepColor value, def;
};
struct aepLayerParamValue
{
    aepLayer *value;
};

aepCLinkage aepExport aepLayer*     aepCreateLayer();
aepCLinkage aepExport void          aepDestroyLayer(aepLayer *layer);
aepCLinkage aepExport void          aepResizeLayer(aepLayer *layer, int width, int height);
aepCLinkage aepExport void          aepGetLayerData(aepLayer *layer, aepLayerData *dst);

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

aepCLinkage aepExport void          aepSetInput(aepInstance *ins, aepLayer *layer);
aepCLinkage aepExport aepLayer*     aepRender(aepInstance *ins, double time, int width, int height);

#endif // AfterEffectsPlugin_h
