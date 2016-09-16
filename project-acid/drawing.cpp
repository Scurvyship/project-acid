#include "drawing.h"
#include "DllMain.h"

int Drawing::DrawString(int x, int y, int r, int g, int b, char *szBuffer, ...) {
    char szTmp[256];
    va_list args;
    va_start(args, szBuffer);
    _vsnprintf(szTmp, sizeof(szTmp), szBuffer, args);
    va_end(args);

    g_Engine.pfnDrawSetTextColor((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f);
	return g_Engine.pfnDrawConsoleString(x, y, szTmp);
}

Drawing g_Drawing;