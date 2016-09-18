#include "client.h"

void HUD_Redraw(float time, int intermission) {
    g_Client.HUD_Redraw(time, intermission);

    cl_entity_t *pLocal = g_Engine.GetLocalPlayer(); // me
    g_Local.iIndex = pLocal->index;
    g_Local.bAlive = pLocal->curstate.solid ? true : false;

    for(unsigned short i = 0; i < 33; i++) {
        player_s &player = g_Player[i];
        cl_entity_s *ent = g_Engine.GetEntityByIndex(i);
        g_Engine.pfnGetPlayerInfo(i,&g_Player[i].Info);

        g_Player[i].bAlive = ent && !(ent->curstate.effects & EF_NODRAW) && ent->player && ent->curstate.movetype != 6 && ent->curstate.movetype != 0;
        g_Player[i].bUpdated = IsEntityValid(ent);
        g_Player[i].iTeam = g_PlayerTeam[i];
        g_Player[i].fDistance = floor(sqrt(POW(abs(player.vOrigin.x - g_Local.vOrigin.x)) + POW(abs(player.vOrigin.y - g_Local.vOrigin.y)) + POW(abs(player.vOrigin.z - g_Local.vOrigin.z)))-32);

        // Draw stuff...
        if(g_Player[i].bUpdated)
            g_Drawing.DrawString(10, 100+i*20, 255, 255, 255, "team: %d       dist: %d", g_Player[i].iTeam, g_Player[i].fDistance);
    }

    //g_Drawing.DrawString(10, 120, 255, 255, 255, "project-acid");
}

void HUD_Frame(double dTime) {
    static bool bInit = true;
    if(bInit && g_pEngine != NULL) {
        g_Engine.Con_Printf("project-acid loaded");

        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SocketStuff, NULL, NULL, NULL);

        bInit = false;
    }

    g_Client.HUD_Frame(dTime);              
}

void HUD_PlayerMove(struct playermove_s *ppmove, int server) {
    g_Client.HUD_PlayerMove(ppmove, server);

    g_Local.vOrigin = ppmove->origin; // Get current vector
    g_Engine.pEventAPI->EV_LocalPlayerViewheight(g_Local.vEye);
    g_Local.vEye    = g_Local.vEye + ppmove->origin;
    g_Local.iFlags  = ppmove->flags;

    float yaw = ppmove->angles[1] * (0.017453);
    g_Local.sinYaw  =  sin(yaw);
    g_Local.mCosYaw = -cos(yaw);
}

void PreS_DynamicSound(int entid, DWORD entchannel, char *szSoundFile, float *fOrigin, float fVolume, float fAttenuation, int iTimeOff, int iPitch) {
    if(entid > 0 && entid < 33 && entid != g_Engine.GetLocalPlayer()->index) {
        VectorCopy(fOrigin, g_Player[entid].vOrigin); // fingers crossed 
    }

    PreS_DynamicSound_s(entid, entchannel, szSoundFile, fOrigin, fVolume, fAttenuation, iTimeOff, iPitch);
}

/* Some misc stuff */
bool IsEntityValid(cl_entity_s *ent) {
    if (ent &&
        ent->player &&
        !ent->curstate.spectator &&
        ent->curstate.solid &&
        ent->index != g_Local.iIndex &&
        ent != g_Engine.GetLocalPlayer() &&
        !(ent->curstate.effects & EF_NODRAW) &&
        !(ent->curstate.messagenum < g_Engine.GetLocalPlayer()->curstate.messagenum) &&
        (ent->model->name != NULL || ent->model->name != "" || ent->model->name != 0)
    ){
        return true;
    }

    return false;
}

/* Hooks */
void HookEngine(void) {
    memcpy( &g_Engine, (LPVOID)g_pEngine, sizeof( cl_enginefunc_t ) );
    g_pEngine->pfnHookUserMsg = pfnHookUserMsg;
}

void HookClient(void) {
    memcpy(&g_Client, (LPVOID)g_pClient, sizeof(cl_clientfunc_t));

    g_pClient->HUD_Frame        = HUD_Frame;
    g_pClient->HUD_Redraw       = HUD_Redraw;
    g_pClient->HUD_PlayerMove   = HUD_PlayerMove;

    // FarESP...
    PreS_DynamicSound_s = (PreS_DynamicSound_t)DetourFunction((LPBYTE)dwSound, (LPBYTE)&PreS_DynamicSound);
}

/* Sockets */
void SocketStuff(void) {
    Socket g_Socket;
    while(1) {
        g_Socket.Send();
        printf("%d\n", g_Socket.counter);

        Sleep(5000);
    }
}