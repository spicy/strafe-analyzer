#pragma once
#include "../Indices/Indices.h"

class IPanel {
public:
	const char* get_panel_name(unsigned int panel_id) {
		using original_fn = const char* (__thiscall*)(IPanel*, unsigned int);
		return (*(original_fn**)this)[Indices::get_panel_name](this, panel_id);
	}
};