#pragma once
#include "DllMain.h"
#include "drawing.h"
#include "socket.h"

bool IsEntityValid(cl_entity_s *ent);
void SocketStuff(void);

local_s g_Local;
player_s g_Player[33];
std::vector<entity_s> g_Entity;