#pragma once
#include "../Interfaces/Interfaces.h"
#include "../minhook/minhook.h"
#include "../sdk+/Entity.h"
#include "../sdk+/sdk.h"

namespace Hooks 
{
	bool Initialize();
	void Release();

	namespace CreateMove 
	{
		typedef bool(__stdcall* CreateMove_fn) (float, CUserCmd*);
		inline CreateMove_fn CreateMove_original;
		bool __fastcall Hook(void* ecx, void* edx, float input_sample_frame_time, CUserCmd* cmd);
	};

	namespace PaintTraverse
	{
		typedef void(__thiscall* PaintTraverse_fn)(IPanel*, unsigned int vguiPanel, bool forceRepaint, bool allowForce);
		inline PaintTraverse_fn PaintTraverse_original;
		void __stdcall Hook(unsigned int panel, bool force_repaint, bool allow_force);
	};

	namespace LockCursor 
	{
		typedef void(__thiscall* LockCursor_fn)(ISurface*);
		inline LockCursor_fn LockCursor_original;
		void __stdcall Hook();
	}

	namespace GameUI
	{
		typedef void(__thiscall* GameUI_fn)(IGameUI*, const char*, int, int, int); //const char*, int, int, int
		inline GameUI_fn GameUI_original;
		void __stdcall Hook(const char* game, int IP, int connectionPort, int queryPort);
	};
}