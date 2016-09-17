#pragma once
#include "DllMain.h"

class Offsets {
    public:
        Offsets();

        bool bInit = false;
        DWORD hwBase, hwSize, hwEnd;
        DWORD hlBase, hlSize, hlEnd;
        DWORD clBase, clSize, clEnd;

        DWORD GetEngineFuncs();
        DWORD GetClientFuncs();
        DWORD GetStudioFuncs();
        DWORD Offsets::PreS_DynamicSound();
};