#include "sdk+/sdk.h"
#include "zgui/zgui.hh"
#include "sdk+/drawing.h"
#include "sdk+/console.h"

#include "analyzer/TickData.h"
#include "analyzer/History.h"
#include "Servers.h"

// #========================================================================================#
// +																						+ 
// +			█▀ ▀█▀ █▀█ ▄▀█ █▀▀ █▀▀   ▄▀█ █▄ █ ▄▀█ █   █▄█ ▀█ █▀▀ █▀█			+
// +			▄█  █  █▀▄ █▀█ █▀  ██▄   █▀█ █ ▀█ █▀█ █▄▄  █  █▄ ██▄ █▀▄			+
// +												                      ᵇʸ ˢᵖⁱᶜʸ			+
// +	Once Compiled, this DLL hooks multiple necessary game functions in CSS/CSGO such	+
// +	as the OnCreateMove function(which is called each tick* when the server updates		+
// +	player data*) so that we can immediately observe the players current state, make	+
// +	calculations, then draw helpful data, like realtime graphs on the players screen	+
// +	so that they know how to improve their ingame movement for speedrunning.			+
// +																						+
// +	The player can enable and disable features on a menu. Each feature on the menu		+
// +	has a corresponding setting value in our header file. We can reference these		+
// +	settings to determine what features the player wants enabled.						+
// +																						+
// #========================================================================================#

std::vector<Server> AllowedServers::servers;

// Define mem for history vectors
std::vector<TickData> History::tickHist;
std::vector<StrafeData> History::strafeHist;
std::vector<TickData> History::recordedRun;

DWORD WINAPI initialize(void* instance)
{
	while (!GetModuleHandleA("serverbrowser.dll"))
		Sleep(200);

	//console::attach("strafe analyzer");

	char buffer[MAX_PATH];
	GetModuleFileName(nullptr, buffer, MAX_PATH);

	game = buffer;

	game.erase(game.find_last_of('\\', game.size()));
	game.erase(0, game.find_last_of('\\') + 1);

	if (strstr(game.c_str(), "Counter-Strike Global Offensive"))
		game_engine = ENGINE_CSGO;
	else if (strstr(game.c_str(), "Counter-Strike Source"))
		game_engine = ENGINE_CSS;

	Indices::Initialize();
	Interfaces::Initialize();
	Hooks::Initialize();
	AllowedServers::Initialize();
	render::setup_fonts();

	zgui::functions.draw_line = render::line_zgui;
	zgui::functions.draw_rect = render::rect_zgui;
	zgui::functions.draw_filled_rect = render::filled_rect_zgui;
	zgui::functions.draw_text = render::text;
	zgui::functions.get_text_size = render::get_text_size;
	zgui::functions.get_frame_time = render::get_frametime;

	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	Hooks::Release();
	Sleep(100);

	//console::release();

	FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
}

BOOL APIENTRY DllMain(void* instance, uintptr_t reason, void* reserved) 
{
	DisableThreadLibraryCalls(static_cast<HMODULE>(instance));
 
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		if (const auto handle = CreateThread(NULL, NULL, initialize, instance, NULL, NULL))
			CloseHandle(handle);
		break;
	default: ;
	}

	return true;
}
