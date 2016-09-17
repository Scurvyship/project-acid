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

DWORD Offsets::PreS_DynamicSound() {
    /*
    $ ==>    > 83EC 48          SUB ESP,48
    $+9C     > 68 8C41F504      PUSH hw.04F5418C ; ASCII "S_StartDynamicSound: %s volume > 255"
    */
    return 0x49c2bc0;
}