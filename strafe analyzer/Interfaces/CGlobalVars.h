#pragma once
#include <cstdint>
#include "../Indices/Indices.h"

class CGlobalVars {
public:
	float frame_time()
	{
		return *reinterpret_cast<float*>(uintptr_t(this) + Indices::frame_time);
	}

	float interval_per_tick()
	{
		return *reinterpret_cast<float*>(uintptr_t(this) + Indices::interval_per_tick);
	}
};
