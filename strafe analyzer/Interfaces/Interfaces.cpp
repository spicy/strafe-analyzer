#include "Interfaces.h"
#include "../SDK+/SDK.h"

IBaseClientDLL* Interfaces::client = nullptr;
IVEngineClient* Interfaces::engine = nullptr;
IClientEntityList* Interfaces::ent_list = nullptr;
IPanel* Interfaces::panel = nullptr;
ISurface* Interfaces::surface = nullptr;
IClientMode* Interfaces::clientmode = nullptr;
CGlobalVars* Interfaces::globals = nullptr;
IConVar* Interfaces::convar = nullptr;
IInputSystem* Interfaces::input = nullptr;
IVDebugOverlay* Interfaces::debugoverlay = nullptr;
IGameUI* Interfaces::gameui = nullptr;

bool Interfaces::Initialize()
{
	client = seek_interface<IBaseClientDLL>("client.dll", "VClient");
	ent_list = seek_interface<IClientEntityList>("client.dll", "VClientEntityList");
	engine = seek_interface<IVEngineClient>("engine.dll", "VEngineClient");
	panel = seek_interface<IPanel>("vgui2.dll", "VGUI_Panel");
	surface = seek_interface<ISurface>("vguimatsurface.dll", "VGUI_Surface");
	convar = seek_interface<IConVar>("materialsystem.dll", "VEngineCvar");
	debugoverlay = seek_interface<IVDebugOverlay>("engine.dll", "VDebugOverlay");
	input = seek_interface<IInputSystem>("inputsystem.dll", "InputSystemVersion");

	if (game_engine == ENGINE_CSGO) gameui = seek_interface<IGameUI>("client.dll", "GameUI");
	else if (game_engine == ENGINE_CSS) gameui = seek_interface<IGameUI>("gameui.dll", "GameUI");

	clientmode = **reinterpret_cast<IClientMode***>((*reinterpret_cast<DWORD**>(client))[10] + 0x5);

	const auto pdw_client = PDWORD(*PDWORD(client));

	const auto dw_init_addr = DWORD(pdw_client[0]);

	for (DWORD dw_iter = 0; dw_iter <= 0xFF; dw_iter++)
	{
		if (*PBYTE(dw_init_addr + dw_iter) == 0xA3)
		{
			globals = reinterpret_cast<CGlobalVars*>(*PDWORD(*PDWORD(dw_init_addr + dw_iter + 1)));

			break;
		}
	}

	if (game_engine == ENGINE_CSGO)
	{
		//EXEC commands first
		Interfaces::engine->execute_cmd_csgo("sv_cheats 1");
		Interfaces::engine->execute_cmd_csgo("sv_lan 1");
		Interfaces::engine->execute_cmd_csgo("retry");
	}
	else
	{
		Interfaces::engine->execute_cmd_css("sv_cheats 1");
		Interfaces::engine->execute_cmd_css("sv_lan 1");
		//Interfaces::engine->execute_cmd_css("retry"); temporary
		//Interfaces::engine->execute_cmd_css("net_graphproportionalfont 0");
	}

	return true;
}
