#ifndef aepInternal_h
#define aepInternal_h

#include "Foundation.h"
#include "AfterEffectsPlugin.h"

#ifndef aepMaster
    #define aepTrace(FMT, ...) utjDebugLog(FMT "\n", __VA_ARGS__)
    #define aepTrace2() utjDebugLog("\n")
#else
    #define aepTrace(FMT, ...) 
    #define aepTrace2() 
#endif

typedef utj::ImageBase aepImage;
typedef utj::ImageRGBAu8 aepImageRGBAu8;
typedef utj::ImageIntrusiveRGBAu8 aepImageIntrusiveRGBA;

PF_InteractCallbacks&   aepGetHostCallbacks();
PF_UtilCallbacks&       aepGetUtilCallbacks();
SPBasicSuite&           aepGetSPBasicSuite();

#include "aepModule.h"
#include "aepInstance.h"
#include "aepParam.h"

#endif // aepInternal_h
