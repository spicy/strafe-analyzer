#pragma once
#include <string>

namespace zgui 
{
	struct color;
}

struct color;
class vec3_t;

namespace render 
{
	enum font_flags 
	{
		fontflag_none,
		fontflag_italic = 0x001,
		fontflag_underline = 0x002,
		fontflag_strikeout = 0x004,
		fontflag_symbol = 0x008,
		fontflag_antialias = 0x010,
		fontflag_gaussianblur = 0x020,
		fontflag_rotary = 0x040,
		fontflag_dropshadow = 0x080,
		fontflag_additive = 0x100,
		fontflag_outline = 0x200,
		fontflag_custom = 0x400,
		fontflag_bitmap = 0x800,
	};

	extern unsigned long moon_font;
	extern unsigned long arial_font;

	void setup_fonts();

	void draw_cursor();

	void line(int x, int y, int x2, int y2, color c) noexcept;
	void circle(int x, int y, int r, int s, color col) noexcept;
	void rect(int x, int y, int x2, int y2, color c) noexcept;
	void filled_rect(int x, int y, int x2, int y2, color c) noexcept;
	void line_zgui(int x, int y, int x2, int y2, zgui::color c) noexcept;
	void rect_zgui(int x, int y, int x2, int y2, zgui::color c) noexcept;
	void filled_rect_zgui(int x, int y, int x2, int y2, zgui::color c) noexcept;
	void text(int x, int y, zgui::color c, int font, bool center, const char* text) noexcept;
	void text(int x, int y, color c, int font, bool center, const char* text) noexcept;
	void s_text(int x, int y, color c, int font, bool center, const std::string& text) noexcept;
	void draw_string(int x, int y, color col, unsigned long font, bool center, const char* pszText, ...);
	void DrawT(int X, int Y, color Color, int Font, bool Center, const char* _Input, ...);
	void get_text_size(unsigned long font, const char* text, int& wide, int& tall) noexcept;
	void get_text_size(unsigned long font, std::string str, int& width, int& height) noexcept;
	float get_frametime() noexcept;
};