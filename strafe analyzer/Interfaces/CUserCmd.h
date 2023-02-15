#pragma once
#include "../Indices/Indices.h"
#include <cstdint>
#include "../math/vector3d.h"

enum cmd_buttons {			// unique flag bit shift
	in_attack = (1 << 0),	// binary 0001
	in_jump = (1 << 1),		// binary 0010
	in_duck = (1 << 2),		// binary 0100
	in_forward = (1 << 3),
	in_back = (1 << 4),
	in_use = (1 << 5),
	in_cancel = (1 << 6),
	in_left = (1 << 7),
	in_right = (1 << 8),
	in_moveleft = (1 << 9),
	in_moveright = (1 << 10),
	in_attack2 = (1 << 11),
	in_run = (1 << 12),
	in_reload = (1 << 13),
	in_alt1 = (1 << 14),
	in_alt2 = (1 << 15),
	in_score = (1 << 16),
	in_speed = (1 << 17),
	in_walk = (1 << 18),
	in_zoom = (1 << 19),
	in_weapon1 = (1 << 20),
	in_weapon2 = (1 << 21),
	in_bullrush = (1 << 22),
	in_grenade1 = (1 << 23),
	in_grenade2 = (1 << 24),
	in_attack3 = (1 << 25)
};

class CUserCmd {
public:
	int command_number()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + Indices::command_number);
	}

	int buttons()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + Indices::buttons);
	}

	int mousedx()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + Indices::mousedx);
	}

	int mousedy()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + Indices::mousedy);
	}

	float sidemove()
	{
		return *reinterpret_cast<float*>(uintptr_t(this) + Indices::sidemove);
	}

	float forwardmove()
	{
		return *reinterpret_cast<float*>(uintptr_t(this) + Indices::forwardmove);
	}

	vec3_t viewangles()
	{
		return *reinterpret_cast<vec3_t*>(uintptr_t(this) + Indices::viewangles);
	}
};