#pragma once
#include <winsock2.h>
#include <Windows.h>
#include <vector>

using namespace std;

#pragma warning (disable:4244)

#include "HLSDK/engine/wrect.h"
#include "HLSDK/engine/cl_dll.h"
#include "HLSDK/engine/r_studioint.h"
#include "HLSDK/engine/cl_entity.h"
#include "HLSDK/misc/com_model.h"
#include "HLSDK/engine/triangleapi.h"
#include "HLSDK/engine/pmtrace.h"
#include "HLSDK/engine/pm_defs.h"
#include "HLSDK/engine/pm_info.h"
#include "HLSDK/common/ref_params.h"
#include "HLSDK/common/studio_event.h"
#include "HLSDK/common/net_api.h"
#include "HLSDK/common/r_efx.h"
#include "HLSDK/engine/cvardef.h"
#include "HLSDK/engine/util_vector.h"
#include "HLSDK/misc/parsemsg.h"
#include "HLSDK/engine/studio.h"
#include "HLSDK/engine/event_args.h"
#include "HLSDK/engine/event_flags.h"
#include "HLSDK/common/event_api.h"
#include "HLSDK/common/screenfade.h"
#include "HLSDK/engine/keydefs.h"
#include "detours.h"

typedef struct cl_clientfuncs_s {
    int ( *Initialize ) ( cl_enginefunc_t *pEnginefuncs, int iVersion );
    int ( *HUD_Init ) ( void );
    int ( *HUD_VidInit ) ( void );
    void ( *HUD_Redraw ) ( float time, int intermission );
    int ( *HUD_UpdateClientData ) ( client_data_t *pcldata, float flTime );
    int ( *HUD_Reset ) ( void );
    void ( *HUD_PlayerMove ) ( struct playermove_s *ppmove, int server );
    void ( *HUD_PlayerMoveInit ) ( struct playermove_s *ppmove );
    char ( *HUD_PlayerMoveTexture ) ( char *name );
    void ( *IN_ActivateMouse ) ( void );
    void ( *IN_DeactivateMouse ) ( void );
    void ( *IN_MouseEvent ) ( int mstate );
    void ( *IN_ClearStates ) ( void );
    void ( *IN_Accumulate ) ( void );
    void ( *CL_CreateMove ) ( float frametime, struct usercmd_s *cmd, int active );
    int ( *CL_IsThirdPerson ) ( void );
    void ( *CL_CameraOffset ) ( float *ofs );
    struct kbutton_s *( *KB_Find ) ( const char *name );
    void ( *CAM_Think ) ( void );
    void ( *V_CalcRefdef ) ( struct ref_params_s *pparams );
    int ( *HUD_AddEntity ) ( int type, struct cl_entity_s *ent, const char *modelname );
    void ( *HUD_CreateEntities ) ( void );
    void ( *HUD_DrawNormalTriangles ) ( void );
    void ( *HUD_DrawTransparentTriangles ) ( void );
    void ( *HUD_StudioEvent ) ( const struct mstudioevent_s *event, const struct cl_entity_s *entity );
    void ( *HUD_PostRunCmd ) ( struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed );
    void ( *HUD_Shutdown ) ( void );
    void ( *HUD_TxferLocalOverrides ) ( struct entity_state_s *state, const struct clientdata_s *client );
    void ( *HUD_ProcessPlayerState ) ( struct entity_state_s *dst, const struct entity_state_s *src );
    void ( *HUD_TxferPredictionData ) ( struct entity_state_s *ps, const struct entity_state_s *pps, struct clientdata_s *pcd, const struct clientdata_s *ppcd, struct weapon_data_s *wd, const struct weapon_data_s *pwd );
    void ( *Demo_ReadBuffer ) ( int size, unsigned char *buffer );
    int ( *HUD_ConnectionlessPacket ) ( struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size );
    int ( *HUD_GetHullBounds ) ( int hullnumber, float *mins, float *maxs );
    void ( *HUD_Frame ) ( double time );
    int ( *HUD_Key_Event ) ( int down, int keynum, const char *pszCurrentBinding );
    void ( *HUD_TempEntUpdate ) ( double frametime, double client_time, double cl_gravity, struct tempent_s **ppTempEntFree, struct tempent_s **ppTempEntActive, int ( *Callback_AddVisibleEntity )( struct cl_entity_s *pEntity ), void ( *Callback_TempEntPlaySound )( struct tempent_s *pTemp, float damp ) );
    struct cl_entity_s *( *HUD_GetUserEntity ) ( int index );
    int ( *HUD_VoiceStatus ) ( int entindex, qboolean bTalking );
    int ( *HUD_DirectorMessage ) ( unsigned char command, unsigned int firstObject, unsigned int secondObject, unsigned int flags );
    int ( *HUD_GetStudioModelInterface ) ( int version, struct r_studio_interface_s **ppinterface, struct engine_studio_api_s *pstudio );
    void ( *HUD_CHATINPUTPOSITION_FUNCTION ) ( int *x, int *y );
    int ( *HUD_GETPLAYERTEAM_FUNCTION ) ( int iplayer );
    void ( *CLIENTFACTORY ) ( void );
}cl_clientfunc_t;

extern cl_clientfunc_t *g_pClient;
extern cl_clientfunc_t g_Client;
extern cl_enginefunc_t *g_pEngine;
extern cl_enginefunc_t g_Engine;
extern engine_studio_api_t *g_pStudio;
extern engine_studio_api_t g_Studio;

// PreS_DynamicSound
typedef void(*PreS_DynamicSound_t)(int, DWORD, char *, float *, float, float, int, int);
extern PreS_DynamicSound_t PreS_DynamicSound_s;
extern DWORD dwSound;

int pfnHookUserMsg( char *szMsgName, pfnUserMsgHook pfn );

void HookClient(void);
void HookEngine(void);

#define M_PI 3.14159265358979323846
#define POW(x) ((x)*(x))
#define VectorLengthSquared(v) ((v)[0]*(v)[0]+(v)[1]*(v)[1]+(v)[2]*(v)[2])
#define VectorDistance(a,b) sqrt(POW((a)[0]-(b)[0])+POW((a)[1]-(b)[1])+POW((a)[2]-(b)[2]))
#define VectorLength(a) sqrt(POW((a)[0])+POW((a)[1])+POW((a)[2]))
#define VectorAdd(a,b,c) {(c)[0]=(a)[0]+(b)[0];(c)[1]=(a)[1]+(b)[1];(c)[2]=(a)[2]+(b)[2];}
#define VectorMul(vec,num,res){(res)[0]=(vec)[0]*(num);(res)[1]=(vec)[1]*(num);(res)[2]=(vec)[2]*(num);}
#define VectorSubtract(a,b,c) {(c)[0]=(a)[0]-(b)[0];(c)[1]=(a)[1]-(b)[1];(c)[2]=(a)[2]-(b)[2];}
#define Square(a) ((a)*(a))

struct local_s {
    int iIndex;
    int iTeam;
    int iFlags;
    //int iClip;
    //int iWeaponID;
    //int iFOV;
    //int iUseHull;
    //int iMovetype;
    //bool bInReload;
    bool bAlive;
    //float m_flNextPrimaryAttack;
    //float flXYspeed;
    //float flMaxSpeed;
    //float flHeight;
    //Vector vForward;
    //Vector vRight;
    //Vector vPunchangle;
    //Vector vNorecoilAng;
    Vector vOrigin;
    Vector vEye;
    //Vector vViewOrg;
    //float sin_yaw, minus_cos_yaw; // RADAR
    float sinYaw, mCosYaw;
};
extern local_s g_Local;

struct player_s {
    int iTeam;
    //bool bVisible;
    bool bUpdated;
    //bool bDucked;
    bool bAlive;
    float fDistance;
    vec3_t vHitboxOrigin[12];
    vec3_t vOrigin;
    hud_player_info_t Info;
};
extern player_s g_Player[33];

struct entity_s {
    int iImportant;
    vec3_t vOrigin;
    char szName[32];
};
extern std::vector<entity_s> g_Entity;

struct netdata_s {
    unsigned short index;
    float x, y;
    float sinYaw, mCosYaw;
};

extern int g_PlayerTeam[33];