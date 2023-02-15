#pragma once
#include "../sdk+/color.h"

class ISurface 
{
public:

	void set_drawing_color(int r, int g, int b, int a = 255) 
	{
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[Indices::set_drawing_color](this, r, g, b, a);
	}

	void set_text_color(int r, int g, int b, int a = 255) 
	{
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[Indices::set_text_color](this, r, g, b, a);
	}

	void surface_get_cursor_pos(int& x, int& y)
	{
		using original_fn = void(__thiscall*)(ISurface*, int&, int&);
		return (*(original_fn**)this)[Indices::get_cursor_pos](this, x, y);
	}

	void draw_filled_rectangle(int x, int y, int w, int h) 
	{
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[Indices::draw_filled_rectangle](this, x, y, x + w, y + h);
	}

	void draw_outlined_rect(int x, int y, int w, int h) 
	{
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[Indices::draw_outlined_rect](this, x, y, x + w, y + h);
	}

	void draw_line(int x1, int y1, int x2, int y2) 
	{
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[Indices::draw_line](this, x1, y1, x2, y2);
	}

	void draw_text_font(unsigned long font) 
	{
		using original_fn = void(__thiscall*)(ISurface*, unsigned long);
		return (*(original_fn**)this)[Indices::draw_text_font](this, font);
	}

	void draw_text_pos(int x, int y) 
	{
		using original_fn = void(__thiscall*)(ISurface*, int, int);
		return (*(original_fn**)this)[Indices::draw_text_pos](this, x, y);
	}

	void draw_render_text(const wchar_t* text, int textLen) 
	{
		using original_fn = void(__thiscall*)(ISurface*, const wchar_t*, int, int);
		return (*(original_fn**)this)[Indices::draw_render_text](this, text, textLen, 0);
	}

	unsigned long font_create() 
	{
		using original_fn = unsigned int(__thiscall*)(ISurface*);
		return (*(original_fn**)this)[Indices::font_create](this);
	}

	bool set_font_glyph(unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags) 
	{
		using original_fn = bool(__thiscall*)(ISurface*, unsigned long, const char*, int, int, int, int, int, int, int);

		return (*(original_fn**)this)[Indices::set_font_glyph](this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}

	void get_text_size(unsigned long font, const wchar_t* text, int& wide, int& tall) 
	{
		using original_fn = void(__thiscall*)(ISurface*, unsigned long, const wchar_t*, int&, int&);
		return (*(original_fn**)this)[Indices::get_text_size](this, font, text, wide, tall);
	}
	
	void get_screen_size(int& width, int& height) 
	{
		using original_fn = void(__thiscall*)(ISurface*, int&, int&);
		return (*(original_fn**)this)[Indices::get_screen_size_surface](this, std::ref(width), std::ref(height));  //width, height
	}

	void unlock_cursor()
	{
		using original_fn = void(__thiscall*)(ISurface*);
		return (*(original_fn**)this)[Indices::unlock_cursor](this);
	}

	void SetCursorAlwaysVisible(bool vis)
	{
		using original_fn = void(__thiscall*)(ISurface*, bool);
		return (*(original_fn**)this)[Indices::set_cursor_always_visible](this, vis);
	}

	void lock_cursor()
	{
		using original_fn = void(__thiscall*)(ISurface*);
		return (*(original_fn**)this)[Indices::lock_cursor](this);
	}
};
