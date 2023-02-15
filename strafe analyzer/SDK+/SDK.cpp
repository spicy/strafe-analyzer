#include "sdk.h"

/*
void c_sdk::un_inject()
{
#ifdef _DEBUG       
	fclose((FILE*)stdin);
	fclose((FILE*)stdout);

	HWND hw_ConsoleHwnd = GetConsoleWindow();
	FreeConsole();
	PostMessageW(hw_ConsoleHwnd, WM_CLOSE, 0, 0);
#endif
	g_hooks.un_hooks();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
*/