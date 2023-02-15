#pragma once
#include "../math/vector3d.h"
#include "../math/VMatrix.hpp"
#include "../Indices/Indices.h"

class IVEngineClient
{
public:
	//i_net_channel* get_net_channel_info() {
	//	using original_fn = i_net_channel * (__thiscall*)(iv_engine_client*);
	//	return (*(original_fn * *)this)[78](this);
	//}
	int get_local_player() {
		using original_fn = int(__thiscall*)(IVEngineClient*);
		return (*(original_fn**)this)[Indices::get_local_player](this);
	}
	//int get_player_for_user_id(int user_id) {
	//	using original_fn = int(__thiscall*)(iv_engine_client*, int);
	//	return (*(original_fn * *)this)[9](this, user_id);
	//}
	//void get_player_info(int index, player_info_t* info) {
	//	using original_fn = void(__thiscall*)(iv_engine_client*, int, player_info_t*);
	//	return (*(original_fn * *)this)[8](this, index, info);
	//}
	void get_screen_size(int& width, int& height) 
	{
		using original_fn = void(__thiscall*)(IVEngineClient*, int&, int&);
		(*(original_fn**)this)[Indices::get_screen_size](this, width, height);
	}

	bool is_in_game() 
	{
		using original_fn = bool(__thiscall*)(IVEngineClient*);
		return (*(original_fn**)this)[Indices::is_in_game](this);
	}

	bool is_connected() 
	{
		using original_fn = bool(__thiscall*)(IVEngineClient*);
		return (*(original_fn**)this)[Indices::is_connected](this);
	}

	void execute_cmd_css(const char* cmd) 
	{
		using original_fn = void(__thiscall*)(IVEngineClient*, const char*);
		(*(original_fn**)this)[Indices::execute_cmd](this, cmd);
	}

	void execute_cmd_csgo(const char* cmd) 
	{
		using original_fn = void(__thiscall*)(IVEngineClient*, const char*, char);
		(*(original_fn**)this)[Indices::execute_cmd](this, cmd, 0);
	}
																													//g_EngineClient->WorldToScreenMatrix();
	VMatrix& world_to_screen_matrix() 
	{											// breaks
		using original_fn = VMatrix&(__thiscall*)(IVEngineClient*);
		return (*(original_fn**)this)[Indices::world_to_screen_matrix](this);	// add args
	}

	//void ClientCmd_Unrestricted(char const* cmd) { typedef void(__thiscall* ofunc)(PVOID, const char*, char); 
	//return getvfunc<ofunc>(this, 114)(this, cmd, 0); }

	void set_view_angles(vec3_t& angles) {
		using original_fn = void(__thiscall*)(IVEngineClient*, vec3_t&);
		(*(original_fn**)this)[Indices::set_view_angles](this, angles);
	}

	void get_view_angles(vec3_t& angles) {
		using original_fn = void(__thiscall*)(IVEngineClient*, vec3_t&);
		(*(original_fn**)this)[Indices::get_view_angles](this, angles);
	}

	//const char* get_level_name() {
	//	using original_fn = const char* (__thiscall*)(iv_engine_client*);
	//	return (*(original_fn * *)this)[53](this);
	//}
};
