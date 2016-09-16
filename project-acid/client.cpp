#include "DllMain.h"
#include "drawing.h"

/* Overloaded funcs */
/*void StudioEntityLight(struct alight_s *plight) {
    g_Studio.StudioEntityLight(plight);
}*/

void HUD_Redraw(float time, int intermission) {
    g_Client.HUD_Redraw(time, intermission);

    g_Drawing.DrawString(10, 120, 255, 255, 255, "project-acid");
}

void HUD_Frame(double dTime) {
    static bool bInit = true;
    if(bInit && g_pEngine != NULL) {
        g_Engine.Con_Printf("project-acid loaded");

        bInit = false;
    }

    g_Client.HUD_Frame(dTime);
}

void HUD_PlayerMove( struct playermove_s *ppmove, int server )
{
    g_Client.HUD_PlayerMove( ppmove, server );
}

int pfnHookUserMsg( char *szMsgName, pfnUserMsgHook pfn) {
    return g_Engine.pfnHookUserMsg(szMsgName, pfn);
}

/* Hooks */
void HookEngine(void) {
    memcpy( &g_Engine, (LPVOID)g_pEngine, sizeof( cl_enginefunc_t ) );
    g_pEngine->pfnHookUserMsg = pfnHookUserMsg;
}

/*void HookStudio(void) {
    memcpy( &g_Studio, (LPVOID)g_pStudio, sizeof( engine_studio_api_t ) );
    g_pStudio->StudioEntityLight = StudioEntityLight;
}*/

void HookClient(void) {
    memcpy(&g_Client, (LPVOID)g_pClient, sizeof(cl_clientfunc_t));
    g_pClient->HUD_Frame = HUD_Frame;
    g_pClient->HUD_Redraw = HUD_Redraw;
    g_pClient->HUD_PlayerMove = HUD_PlayerMove;
}