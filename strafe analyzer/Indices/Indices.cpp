#include "../SDK+/SDK.h"

void Indices::Initialize()
{
	if (game_engine == ENGINE_CSGO)
	{
		// hooks
		create_move_idx = 24;
		paint_traverse_idx = 41;

		// ibaseclient
		get_client_classes = 8;

		// ivengineclient
		get_local_player = 12;
		get_screen_size = 5;
		is_in_game = 26;
		is_connected = 27;
		execute_cmd = 114;
		get_view_angles = 18;
		set_view_angles = 19;

		//onconnect
		onconnect = 23;

		// surface
		set_drawing_color = 15;
		set_text_color = 25;
		draw_filled_rectangle = 16;
		draw_outlined_rect = 18;
		draw_line = 19;
		draw_text_font = 23;
		draw_text_pos = 26;
		draw_render_text = 28;
		font_create = 71;
		set_font_glyph = 72;
		get_text_size = 79;
		get_screen_size_surface = 44;
		unlock_cursor = 66;
		lock_cursor = 67;
		get_cursor_pos = 100;
		set_cursor_always_visible = 52;

		// input_system
		enable_input = 11;

		// panel
		get_panel_name = 36;

		// c_usercmd
		command_number = 0x4;
		viewangles = 0xC;
		forwardmove = 0x24;
		sidemove = 0x28;
		buttons = 0x30;
		mousedx = 0x44;
		mousedy = 0x48;

		// globals
		frame_time = 0x14;
		interval_per_tick = 0x20;

		//ivdebug
		world_to_screen = 13;

		//w2sm
		world_to_screen_matrix = 37;

		// convar
		get_convar = 16;
	}
	else if (game_engine == ENGINE_CSS)
	{
		// hooks
		create_move_idx = 21;
		paint_traverse_idx = 41;

		// ibaseclient
		get_client_classes = 8;

		// ivengineclient
		get_local_player = 12;
		get_screen_size = 5;
		is_in_game = 26;
		is_connected = 27;
		execute_cmd = 102;
		get_view_angles = 19;
		set_view_angles = 20;

		//onconnect
		onconnect = 30;

		// surface
		set_drawing_color = 11;
		set_text_color = 19;
		draw_filled_rectangle = 12;
		draw_outlined_rect = 14;
		draw_line = 15;
		draw_text_font = 17;
		draw_text_pos = 20;
		draw_render_text = 22;
		font_create = 66;
		set_font_glyph = 67;
		get_text_size = 75;
		get_screen_size_surface = 42;
		unlock_cursor = 60;
		lock_cursor = 61;
		get_cursor_pos = 96;
		set_cursor_always_visible = 52;

		// input_system
		enable_input = 7;

		// panel
		get_panel_name = 36;

		// c_usercmd
		command_number = 0x4;
		viewangles = 0xC;
		forwardmove = 0x18;
		sidemove = 0x1C;
		buttons = 0x24;
		mousedx = 0x38;
		mousedy = 0x3C;

		// globals
		frame_time = 0x10;
		interval_per_tick = 0x1C;

		//ivdebug
		world_to_screen = 9;

		//w2sm
		world_to_screen_matrix = 36;

		// convar
		get_convar = 13;
	}
}
