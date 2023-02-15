#pragma once

namespace Indices
{
	void Initialize();

	// hooks
	inline int create_move_idx;
	inline int paint_traverse_idx;

	// ibaseclient
	inline int get_client_classes;

	// ivengineclient
	inline int get_local_player;
	inline int get_screen_size;
	inline int is_in_game;
	inline int is_connected;
	inline int execute_cmd;
	inline int set_view_angles;
	inline int get_view_angles;
	inline int world_to_screen;

	// surface
	inline int set_drawing_color;
	inline int set_text_color;
	inline int set_cursor_always_visible;
	inline int draw_filled_rectangle;
	inline int draw_outlined_rect;
	inline int draw_line;
	inline int draw_text_font;
	inline int draw_text_pos;
	inline int draw_render_text;
	inline int font_create;
	inline int set_font_glyph;
	inline int get_text_size;
	inline int get_screen_size_surface;
	inline int unlock_cursor;
	inline int lock_cursor;
	inline int get_cursor_pos;

	//connect
	inline int onconnect;

	// input_system
	inline int enable_input;

	// panel
	inline int get_panel_name;

	// c_usercmd
	inline int command_number;
	inline int viewangles;
	inline int buttons;
	inline int sidemove;
	inline int forwardmove;
	inline int mousedx;
	inline int mousedy;

	// globals
	inline int frame_time;
	inline int interval_per_tick;

	//w2sm
	inline int world_to_screen_matrix;

	// convar
	inline int get_convar;
}