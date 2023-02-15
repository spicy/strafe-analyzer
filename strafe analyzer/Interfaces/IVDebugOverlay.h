#include <vector>
#include <string>
#include "../math/vector3d.h"
#include "../Indices/Indices.h"

class IVDebugOverlay {
public:
	//bool world_to_screen(const vec3_t& in, vec3_t& out) {
	//	using original_fn = int(__thiscall*)(IVDebugOverlay*, const vec3_t&, vec3_t&);
	//	int return_value = (*(original_fn**)this)[Indices::world_to_screen](this, in, out);
	//	return static_cast<bool>(return_value != 1);
	//}


	//bool screen_position(const vec3_t& in, vec3_t& out) {
	//	using original_fn = bool(__thiscall*)(IVDebugOverlay*, const vec3_t&, vec3_t&);
	//	return (*(original_fn**)this)[Indices::screen_position](this, std::ref(in), std::ref(out));
	//}
};	