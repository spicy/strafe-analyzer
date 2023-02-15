#pragma once
#include "RouteTool.h"

#include "../AnalyzerInlines.h"
#include "../History.h"
#include "../../zgui/Menu.h"

#include "../../SDK+/Drawing.h"
#include "../../SDK+/Color.h"

namespace RouteTool
{
	/// <summary>
	/// Handle updating recorded run
	/// </summary>
	void Update()
	{
		// Capture input if in menu
		if (g_menu.routetool.menu.enabled)
		{
			if (!g_menu.routetool.recording)
			{
				// F1 enable recording
				if (GetAsyncKeyState(VK_F1))
				{
					g_menu.routetool.recording = true;
					g_menu.routetool.menu.menuText = "Started recording!";
				}
			}
			else
			{
				// F2 disable recording
				if (GetAsyncKeyState(VK_F2))
				{
					g_menu.routetool.recording = false;
					g_menu.routetool.hasRunRecorded = true;
					g_menu.routetool.menu.menuText = "Stopped recording!";

					// Find the first tick where the player jumps or falls
					if (History::recordedRun.size() > 1)
					{
						for (int i = 0; i < History::recordedRun.size() - 1; i++)
						{
							if (History::recordedRun[i].vecVel.z != History::recordedRun[0].vecVel.z)
							{
								g_menu.routetool.firstTickJumped = i;
								break;
							}
						}
					}
				}
			}
			// F3 clear run
			if (GetAsyncKeyState(VK_F3))
			{
				History::recordedRun.clear();
				g_menu.routetool.hasRunRecorded = false;
				g_menu.routetool.menu.menuText = "Cleared recorded run!";
			}
		}

		// Add the current ticks data to vector History::recordedRun
		// If recording
		if (g_menu.routetool.recording)
		{
			const int CUR_TICK = History::tickHist.size() - 1;
			History::recordedRun.push_back(History::tickHist[CUR_TICK]);
		}
	}


	/// <summary>
	/// Get the paths color for a given tick
	/// Tick must be valid
	/// </summary>
	color GetPathTickColor(int index)
	{
		if (History::recordedRun[index].posType == PositionType::GROUND)
		{
			return g_menu.colors.pathOnGround;
		}
		else if (History::recordedRun[index].crouching)
		{
			return g_menu.colors.pathOnCrouch;
		}
		else if (g_menu.routetool.showSpeedLoss && History::recordedRun[index].lostSpeed)
		{
			return g_menu.colors.pathLostSpeed;
		}
		else return g_menu.colors.pathDefault;
	}


	/// <summary>
	/// Draws all necessary portions of History::recordedRun to the world
	/// </summary>
	void Paint()
	{
		if (g_menu.routetool.draw.enabled)
		{
			// Line
			if (g_menu.routetool.draw.pathType == (int)RouteToolGraphType::GRAPH_LINE)
			{
				if (History::recordedRun.size() > 2)
				{
					for (int i = 0; i < History::recordedRun.size() - 2; i++)
					{
						double diffDist = fabs(std::hypot(History::recordedRun[i].vecPos.x - player->origin().x,
							History::recordedRun[i].vecPos.y - player->origin().y,
							History::recordedRun[i].vecPos.z - player->origin().z));

						if (diffDist < g_menu.routetool.drawDistance)
						{
							vec3_t screen, screen2;
							if (worldToScreen(History::recordedRun[i].vecPos, screen))
							{
								if (worldToScreen(History::recordedRun[i + 1].vecPos, screen2))
								{
									color tempColor = GetPathTickColor(i);
									render::line(screen.x, screen.y, screen2.x, screen2.y, tempColor);
								}
							}
						}
					}
				}
			}
			// Dot
			else if (g_menu.routetool.draw.pathType == (int)RouteToolGraphType::GRAPH_DOT)
			{
				if (History::recordedRun.size() > 1)
				{
					for (int i = 0; i < History::recordedRun.size() - 1; i++)
					{
						double diffDist = fabs(std::hypot(History::recordedRun[i].vecPos.x - player->origin().x,
							History::recordedRun[i].vecPos.y - player->origin().y,
							History::recordedRun[i].vecPos.z - player->origin().z));

						if (diffDist < g_menu.routetool.drawDistance)
						{
							vec3_t screen;
							if (worldToScreen(History::recordedRun[i].vecPos, screen))
							{
								color tempColor = GetPathTickColor(i);
								render::filled_rect(screen.x, screen.y, g_menu.routetool.lineSize, g_menu.routetool.lineSize, tempColor);
							}
						}
					}
				}
			}
		}
		if (g_menu.routetool.menu.enabled)
		{
			// Draw background
			render::filled_rect(30, 30, 145, 100, g_menu.colors.bg);
			// Draw text
			render::s_text(50, 40, color::white(255), render::moon_font, false, "F1 - Start recording");
			render::s_text(50, 60, color::white(255), render::moon_font, false, "F2 - Stop recording");
			render::s_text(50, 80, color::white(255), render::moon_font, false, "F3 - Clear recording");
			render::s_text(50, 100, color::green(255), render::moon_font, false, g_menu.routetool.menu.menuText);
		}
	}
}
