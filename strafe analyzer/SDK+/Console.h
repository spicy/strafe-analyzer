#pragma once
#include "sdk.h"

namespace console {
	void attach(const char* title);
	void release();
	void log_angles(const vec3_t& angles);
	void log(const char* format, ...);
}