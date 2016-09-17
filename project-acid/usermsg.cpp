#include "DllMain.h"
#define HOOK_MSG(msgName) if(!strcmp(szMsgName, #msgName)) { p##msgName = pfn; return g_Engine.pfnHookUserMsg(szMsgName, ##msgName); }

pfnUserMsgHook pTeamInfo  = NULL;
pfnUserMsgHook pDeathMsg  = NULL;
pfnUserMsgHook pCurWeapon = NULL;
pfnUserMsgHook pSetFOV    = NULL;

int g_PlayerTeam[33];

int TeamInfo(const char *pszName, int iSize, void *pbuf) {
    BEGIN_READ(pbuf, iSize);
    int iIndex = READ_BYTE();
    char *szTeam = READ_STRING();
    if(!strcmp(szTeam, "TERRORIST")) {
        g_Player[iIndex].iTeam = 1;
        if(iIndex == g_Local.iIndex) g_Local.iTeam = 1;
        g_PlayerTeam[iIndex] = 1;
    }else if(!strcmp(szTeam,"CT")) {
        g_Player[iIndex].iTeam = 2;
        if(iIndex == g_Local.iIndex) g_Local.iTeam = 2;
        g_PlayerTeam[iIndex] = 2;
    }else { // SPECTATOR
        g_Player[iIndex].iTeam = 0;
        if(iIndex == g_Local.iIndex) g_Local.iTeam = 0;
        g_PlayerTeam[iIndex] = 0;
    }
    return (*pTeamInfo)(pszName, iSize, pbuf);
}

int DeathMsg(const char *pszName, int iSize, void *pbuf) {
    BEGIN_READ(pbuf, iSize);
    int iKiller   = READ_BYTE();
    int iVictim   = READ_BYTE();
    int iHeadshot = READ_BYTE();
    char* pszWeaponName = READ_STRING();
    g_Player[iVictim].bUpdated = false;
    g_Player[iVictim].bAlive   = false;
    if(iVictim == g_Local.iIndex) g_Local.bAlive = false;
    return (*pDeathMsg)(pszName, iSize, pbuf);
}

int pfnHookUserMsg(char *szMsgName, pfnUserMsgHook pfn) {
    HOOK_MSG(TeamInfo);
    HOOK_MSG(DeathMsg);

    return g_Engine.pfnHookUserMsg( szMsgName, pfn );
}