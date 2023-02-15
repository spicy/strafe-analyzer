#include <stdexcept>
#include "hooks.h"
#include "../sdk+/drawing.h"

unsigned int get_virtual(void* class_, unsigned int index) { return static_cast<unsigned int>((*static_cast<int**>(class_))[index]); }

bool Hooks::Initialize() 
{
	const auto CreateMove_target = reinterpret_cast<void*>(get_virtual(Interfaces::clientmode, Indices::create_move_idx));
	const auto PaintTraverse_target = reinterpret_cast<void*>(get_virtual(Interfaces::panel, Indices::paint_traverse_idx));
	const auto LockCursor_target = reinterpret_cast<void*>(get_virtual(Interfaces::surface, Indices::lock_cursor));
	const auto GameUI_target = reinterpret_cast<void*>(get_virtual(Interfaces::gameui, Indices::onconnect));

	if (MH_Initialize() != MH_OK) 
	{
		throw std::runtime_error("failed to initialize MH_Initialize.");
		return false;
	}

	if (MH_CreateHook(CreateMove_target, &CreateMove::Hook, reinterpret_cast<void**>(&CreateMove::CreateMove_original)) != MH_OK) 
	{
		throw std::runtime_error("failed to initialize create_move. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(PaintTraverse_target, &PaintTraverse::Hook, reinterpret_cast<void**>(&PaintTraverse::PaintTraverse_original)) != MH_OK)
	{
		throw std::runtime_error("failed to initialize paint_traverse. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(LockCursor_target, &LockCursor::Hook, reinterpret_cast<void**>(&LockCursor::LockCursor_original)) != MH_OK) 
	{
		throw std::runtime_error("failed to initialize lock_cursor. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(GameUI_target, &GameUI::Hook, reinterpret_cast<void**>(&GameUI::GameUI_original)) != MH_OK) 
	{
		throw std::runtime_error("failed to initialize gameui. (outdated index?)");
		return false;
	}
	
	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) 
	{
		throw std::runtime_error("failed to enable hooks.");
		return false;
	}

	//console::log("hooks initialized");

	return true;
}

void Hooks::Release() {
	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);

	Interfaces::input->enable_input(true);
}