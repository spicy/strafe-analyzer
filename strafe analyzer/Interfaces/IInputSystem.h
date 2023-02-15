#pragma once

class IInputSystem
{
public:
	void enable_input(bool bEnable) 
	{
		using original_fn = void(__thiscall*)(void*, bool);
		return (*reinterpret_cast<original_fn**>(this))[Indices::enable_input](this, bEnable);
	}
};
