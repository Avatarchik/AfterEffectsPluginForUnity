#ifndef AfterEffectsPluginForUnity_h
#define AfterEffectsPluginForUnity_h

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


aepCLinkage aepExport aepModule*    aepLoadModule(const char *path);
aepCLinkage aepExport void          aepUnloadModule(aepModule *mod);

aepCLinkage aepExport void          aepRender(aepModule *mod);

#endif // AfterEffectsPluginForUnity_h
