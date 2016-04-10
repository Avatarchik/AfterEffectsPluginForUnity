#include <cstdio>
#include <vector>
#include "../AfterEffectsPlugin/AfterEffectsPlugin.h"
#pragma warning(disable:4996)


int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s plugin_path\n", argv[0]);
        return 0;
    }

    aepModule *mod = aepLoadModule(argv[1]);
    if (!mod) {
        printf("failed to load module: %s\n", argv[1]);
    }
    aepInstance *inst = aepCreateInstance(mod);

    {
        aepParamInfo info;
        int nparams = aepGetNumParams(inst);
        printf("params:\n");
        for (int i = 0; i < nparams; ++i) {
            aepParam *param = aepGetParam(inst, i);
            aepGetParamInfo(param, &info);
            printf("  %s (%d)\n", info.name, info.type);
        }
    }

    aepDestroyInstance(inst);
    aepUnloadModule(mod);
}
