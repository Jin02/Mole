// WIPIMain.cpp : Defines the entry point for the DLL application.
//
#include		<windows.h>

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}


__declspec(dllexport) void handleCletEvent	(int type, int param1, int param2);
__declspec(dllexport) void startClet		(int argc, char *argv[]);
__declspec(dllexport) void pauseClet		(void);
__declspec(dllexport) void resumeClet		(void);
__declspec(dllexport) void destroyClet		(void);
__declspec(dllexport) void paintClet		(int x, int y, int w, int h);
