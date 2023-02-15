#pragma once
#include <cstddef>
#include <string>
#include <Windows.h>

#include "IBaseClientDLL.h"
#include "IClientEntityList.h"
#include "IVEngineClient.h"
#include "IPanel.h"
#include "ISurface.h"
#include "IConVar.h"
#include "IInputSystem.h"
#include "IVDebugOverlay.h"
#include "CUserCmd.h"
#include "CGlobalVars.h"
#include "IGameUI.h"


namespace Interfaces 
{
	template< typename T >
	T* seek_interface(char* mod, char* interf, bool print = false, bool seek = true)
	{
		typedef T* (*CreateInterfaceFn)(const char* szName, int iReturn);
		CreateInterfaceFn CreateInterface = CreateInterfaceFn(GetProcAddress(GetModuleHandleA(mod), ("CreateInterface")));

		std::string s_interface_version = "0";

		if (seek)
		{
			for (auto i = 0; i <= 99; i++)
			{
				std::string s_interface = interf;
				s_interface += s_interface_version;
				s_interface += std::to_string(i);

				T* funcPtr = CreateInterface(s_interface.c_str(), NULL);

				if (funcPtr != nullptr)
				{
					if (print)
						printf(" -- Found interface pointer for '%s' ==> 0x%p\n", s_interface.c_str(), funcPtr);
					return funcPtr;
				}

				if (i == 99 && s_interface_version == "0")
				{
					s_interface_version = "00";
					i = 0;
				}
				else if (i == 99 && s_interface_version == "00")
				{
					return nullptr;
				}
			}
		}
		else
		{
			T* ptr = CreateInterface(interf, 0);

			if (ptr)
			{
				if (print)
					printf(" -- Found interface pointer for '%s' ==> 0x%p\n", interf, ptr);
				return ptr;
			}
			else
			{
				return nullptr;
			}
		}

		return nullptr;
	}

	extern IBaseClientDLL* client;
	extern IVEngineClient* engine;
	extern IClientEntityList* ent_list;
	extern IPanel* panel;
	extern ISurface* surface;
	extern IClientMode* clientmode;
	extern CGlobalVars* globals;
	extern IConVar* convar;
	extern IInputSystem* input;
	extern IVDebugOverlay* debugoverlay;
	extern IGameUI* gameui;

	bool Initialize();
}
