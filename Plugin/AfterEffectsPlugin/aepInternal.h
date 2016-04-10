#ifndef aepInternal_h
#define aepInternal_h

#include "Foundation.h"
#include "AfterEffectsPlugin.h"

#ifndef aepMaster
    #define aepTrace(FMT, ...) utjDebugLog(FMT "\n", __VA_ARGS__)
#else
    #define aepTrace(FMT, ...) 
#endif
PF_InteractCallbacks&   aepGetHostCallbacks();
PF_UtilCallbacks&       aepGetUtilCallbacks();

#include "aepModule.h"
#include "aepInstance.h"
#include "aepParam.h"

#endif // aepInternal_h
