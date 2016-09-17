#pragma once
#include "DllMain.h"
#include "offsets.h"

cl_clientfunc_t *g_pClient = nullptr;
cl_clientfunc_t g_Client;
cl_enginefunc_t *g_pEngine = nullptr;
cl_enginefunc_t g_Engine;
engine_studio_api_t *g_pStudio = nullptr;
engine_studio_api_t g_Studio;

int __cdecl AddCommand(char *szCmdName, void (*function)(void)) {
    __asm {
        nop;
    }

    return 0;
}

cvar_t *RegisterVariable(char *szVarName, char *szVarValue, int flags) {
    cvar_t *pResult = g_Engine.pfnGetCvarPointer(szVarName);
    if(pResult) return pResult;
    return g_Engine.pfnRegisterVariable(szVarName, szVarValue, flags);
}

void __stdcall DoHooks() {
    Offsets g_Offsets;
    while(!g_Offsets.bInit)
        Sleep(100);

    // Hooked?
    g_pClient = (cl_clientfunc_t*)g_Offsets.GetClientFuncs();
    g_pEngine = (cl_enginefunc_t*)g_Offsets.GetEngineFuncs();
    g_pStudio = (engine_studio_api_t*)g_Offsets.GetStudioFuncs();

    if(!g_pClient || !g_pEngine || !g_pStudio) {
        MessageBox(NULL, "Hook failed.", "acid", MB_OK);
    }

    RtlCopyMemory(&g_Client, g_pClient, sizeof(cl_clientfunc_t));
    RtlCopyMemory(&g_Engine, g_pEngine, sizeof(cl_enginefunc_t));
    RtlCopyMemory(&g_Studio, g_pStudio, sizeof(engine_studio_api_t));

    HookClient();

    g_pEngine->pfnHookUserMsg = &pfnHookUserMsg;
    g_pEngine->pfnAddCommand = &AddCommand;
    g_pEngine->pfnRegisterVariable = &RegisterVariable;

    g_Client.Initialize(g_pEngine, CLDLL_INTERFACE_VERSION);
    g_Client.HUD_Init();

    g_pEngine->pfnHookUserMsg = g_Engine.pfnHookUserMsg;
    g_pEngine->pfnAddCommand = g_Engine.pfnAddCommand;
    g_pEngine->pfnRegisterVariable = g_Engine.pfnRegisterVariable;

    HookEngine();
    //HookStudio();
}

BOOL _declspec(dllexport) APIENTRY DllMain( HANDLE hModule, DWORD dwReason, LPVOID lpReserved ) {
    if(dwReason == DLL_PROCESS_ATTACH ) {
        AllocConsole();
        freopen("CONOUT$", "w", stdout);

        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)DoHooks, NULL, NULL, NULL);
    }
    return TRUE;
}