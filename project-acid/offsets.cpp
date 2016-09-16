#include "offsets.h"

Offsets::Offsets() {
    hwBase = (DWORD)GetModuleHandle("hw.dll");
	hwSize = (DWORD)0x0122A000; // v43
	hwEnd = hwBase + hwSize - 1;

    if(hwBase && hwSize) this->bInit = true;
}

DWORD Offsets::GetEngineFuncs() {
    return 0x4a86a98; // v43
}

DWORD Offsets::GetClientFuncs() {
    return 0x5b1e320; // v43
}

DWORD Offsets::GetStudioFuncs() {
    return *(PDWORD)((DWORD)g_pClient->Initialize + 0x1C); // v43
}