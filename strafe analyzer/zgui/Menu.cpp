#include "menu.h"
#include "zgui.hh"

#include "../sdk+/sdk.h"
#include "../sdk+/drawing.h"

#include "../analyzer/AnalyzerEnums.h"

#include "../Servers.h"

c_menu g_menu;

/// <summary>
/// Calls the enabled zgui tab function to handle menu draws
/// </summary>
/// <param name="game"></param>
void c_menu::Render(std::string game)
{
	zgui::poll_input(game.c_str());
	if (zgui::begin_window("spicy's strafe analyzer", { 615, 357 }, render::moon_font, zgui::zgui_window_flags_none))
	{
		if (zgui::tab_button("Menu", { 40, 30 }, tabs.mainMenu))
		{
			tabs.mainMenu = true;
			tabs.servers = false;
			tabs.strafeTrainer = false;
			tabs.keys = false;
			tabs.routetool = false;
			tabs.misc = false;
		}

		if (zgui::tab_button("Servers", { 40, 30 }, tabs.servers))
		{
			tabs.mainMenu = false;
			tabs.servers = true;
			tabs.strafeTrainer = false;
			tabs.keys = false;
			tabs.routetool = false;
			tabs.misc = false;
		}

		if (zgui::tab_button("Trainer", { 40, 30 }, tabs.strafeTrainer))
		{
			tabs.mainMenu = false;
			tabs.servers = false;
			tabs.strafeTrainer = true;
			tabs.keys = false;
			tabs.routetool = false;
			tabs.misc = false;
		}

		if (zgui::tab_button("Keys", { 40, 30 }, tabs.keys))
		{
			tabs.mainMenu = false;
			tabs.servers = false;
			tabs.strafeTrainer = false;
			tabs.keys = true;
			tabs.routetool = false;
			tabs.misc = false;
		}

		if (zgui::tab_button("Route", { 40, 30 }, tabs.routetool))
		{
			tabs.mainMenu = false;
			tabs.servers = false;
			tabs.strafeTrainer = false;
			tabs.keys = false;
			tabs.routetool = true;
			tabs.misc = false;
		}

		if (zgui::tab_button("Misc", { 40, 30 }, tabs.misc))
		{
			tabs.mainMenu = false;
			tabs.servers = false;
			tabs.strafeTrainer = false;
			tabs.keys = false;
			tabs.routetool = false;
			tabs.misc = true;
		}

		//Call functions now that the tabs are properly set

		if (tabs.mainMenu) MainMenuTab();

		if (tabs.servers) ServersTab();

		if (tabs.strafeTrainer) StrafeTrainerTab();

		if (tabs.keys) KeysTab();

		if (tabs.routetool) RouteToolTab();

		if (tabs.misc) MiscTab();

		zgui::end_window();

		// Renders cursor
		/*
		if (game_engine == ENGINE_CSS)
		{
			if (menu_open)
			{
				Interfaces::surface->SetCursorAlwaysVisible(true);
				render::draw_cursor();
			}
			else Interfaces::surface->SetCursorAlwaysVisible(false);
		}*/

		if (game_engine == ENGINE_CSS)
		{
			if (menu_open)
			{
				Interfaces::input->enable_input(false);
				Interfaces::surface->SetCursorAlwaysVisible(true);
	 		}
			else
			{
				Interfaces::input->enable_input(true);
				Interfaces::surface->SetCursorAlwaysVisible(false);
			}
		}
	}
}


void c_menu::MainMenuTab()
{
	zgui::next_column(50, 0);
	zgui::begin_groupbox("", { 530, 320 }, 0);
	{
		//FREE
		zgui::text("****NEWS**FLASH**** Strafe Analyzer (free)");
		zgui::text("Hello! I hope you enjoy the free practice tool!");
		zgui::text("Your support is the reason I still work on this in the first place.");
		zgui::text("So please consider supporting me through patreon!");
		zgui::text("As this project is still in development, let me know if there are any bugs spicy#7453");
		zgui::text("Please show this off to your friends. Thanks!!");
	}
	zgui::end_groupbox();
}


void c_menu::ServersTab()
{
	zgui::next_column(50, 0);
	zgui::begin_groupbox("", { 530, 320 }, 0);
	{
		//FREE
		zgui::text("Choose a gamemode type to see all servers that support the analyzer!");
		zgui::combobox("Gamemodes #Gamemodes", { "Bhop", "Surf", "KZ", "HNS" }, g_menu.gamemode);
	
		zgui::dummy();

		// Loop through all servers
		for (int i = 0; i < AllowedServers::servers.size(); i++)
		{
			// If the server is the correct engine that we are on
			if (AllowedServers::servers[i].GetEngine() == game_engine)
			{
				// If the server is the selected gamemode filter
				if (AllowedServers::servers[i].GetGamemode() == static_cast<Gamemodes>(g_menu.gamemode))
				{
					std::string text = "Join " + AllowedServers::servers[i].GetName() 
									+ " #" + AllowedServers::servers[i].GetName();
					const char* textConverted = text.c_str();

					// This draws the text, and if clicked it connects to the servers IP
					if (zgui::clickable_text(textConverted))
					{
						
						std::string text2 = "connect " + AllowedServers::servers[i].GetIp() + ":"
											+ AllowedServers::servers[i].GetPort();
						const char* textConverted2 = text2.c_str();

						if (game_engine == ENGINE_CSGO)
						{
							Interfaces::engine->execute_cmd_csgo(textConverted2);
						}
						else
						{
							Interfaces::engine->execute_cmd_css(textConverted2);
						}
					}
				}
			}
		}
	}
	zgui::end_groupbox();
}


void c_menu::StrafeTrainerTab()
{
	zgui::next_column(50, 0);
	zgui::begin_groupbox("", { 260, 320 }, 0);
	{
		zgui::checkbox("Strafe Trainer #StrafeTrainer", g_menu.strafetrainer.enabled);
		zgui::checkbox("Graph Smoothing #Smooth", g_menu.strafetrainer.smooth);
		zgui::checkbox("Invert graph direction #Invert", g_menu.strafetrainer.invertDir);
		zgui::dummy();

		zgui::combobox("Graph Style #GraphStyle", { "Filled Graph", "Line Graph", "Horizontal", "Vertical" }, g_menu.strafetrainer.graphType);

		if (g_menu.strafetrainer.graphType == static_cast<int>(StrafeTrainerGraphType::GRAPH_LINE)
			|| g_menu.strafetrainer.graphType == static_cast<int>(StrafeTrainerGraphType::GRAPH_HORIZONTAL)
				|| g_menu.strafetrainer.graphType == static_cast<int>(StrafeTrainerGraphType::GRAPH_VERTICAL))
		{
			zgui::slider_int("Line Size #lineSize", 1, 10, g_menu.strafetrainer.lineSize, 50);
		}
		zgui::dummy();

		zgui::checkbox("Centered? #stCentered", g_menu.strafetrainer.centered);
		zgui::slider_int("X-position #stXoffset", 0, 2560, g_menu.strafetrainer.xOffset, 50);
		zgui::same_line();
		zgui::slider_int("Y-position #stYoffset", 0, 1440, g_menu.strafetrainer.yOffset, 50);

	}
	zgui::end_groupbox();

	zgui::next_column(270, 0);
	zgui::begin_groupbox("", { 260, 320 }, 0);
	{
		zgui::slider_int("History Size #historySize", 0, 500, g_menu.strafetrainer.historySize, 150);
		zgui::slider_int("Data Width #DataWidth", 1, 15, g_menu.strafetrainer.dataWidth, 150);
		zgui::slider_int("Data Height #DataHeight", 1, 40, g_menu.strafetrainer.dataHeight, 150);
		zgui::slider_float("Speed Loss Tolerance #speedLossTolerance", 0.01, 5, g_menu.strafetrainer.speedLossTolerance);

		zgui::dummy();

		zgui::text("Perf Angle Color");
		zgui::colorpicker("Perf Angle #perfColor", g_menu.strafetrainer.colors.perfColor);
		zgui::text("Synced Color");
		zgui::colorpicker("Synced #Synced", g_menu.strafetrainer.colors.synced);
		zgui::text("UnSynced Color");
		zgui::colorpicker("UnSynced #notSynced", g_menu.strafetrainer.colors.notSynced);
		zgui::text("Counter Strafing Color");
		zgui::colorpicker("Counter Strafing #CounterStrafe", g_menu.strafetrainer.colors.counterStrafe);
	}
	zgui::end_groupbox();
}


void c_menu::KeysTab()
{
	zgui::next_column(50, 0);
	zgui::begin_groupbox("", { 260, 320 });
	{
		zgui::checkbox("Sync Trainer #syncTrainer", g_menu.synctrainer.enabled);
		zgui::checkbox("Stats #KeypressStats", g_menu.synctrainer.statistics);
		zgui::slider_int("Keypress History #KeypressHistory", 1, 15, g_menu.synctrainer.strafeHistorySize, 150);
	}
	zgui::end_groupbox();

	zgui::next_column(270, 0);
	zgui::begin_groupbox("", { 260, 320 }, 0);
	{
		zgui::text("Color Even");
		zgui::colorpicker("Color Even #STLeft", g_menu.synctrainer.colors.leftDir);
		zgui::text("Color Odd");
		zgui::colorpicker("Color Odd #STRight", g_menu.synctrainer.colors.rightDir);
	}
	zgui::end_groupbox();
}


void c_menu::RouteToolTab()
{
	zgui::next_column(50, 0);
	zgui::begin_groupbox("", { 260, 320 });
	{
		zgui::checkbox("Open record route menu #RouteMenu", g_menu.routetool.menu.enabled);
		zgui::checkbox("Draw recorded route #DrawRoute", g_menu.routetool.draw.enabled);

		zgui::dummy();

		zgui::combobox("Path Style #PathStyle", { "Line Path", "Dot Path" }, g_menu.routetool.draw.pathType);
		zgui::slider_int("Draw Distance (units) #PathDrawDistance", 1, 2000, g_menu.routetool.drawDistance, 50);

		zgui::dummy();

		zgui::checkbox("Show speed loss #PathShowSpeedLoss", g_menu.routetool.showSpeedLoss);
	}
	zgui::end_groupbox();

	zgui::next_column(270, 0);
	zgui::begin_groupbox("", { 260, 320 }, 0);
	{
		zgui::slider_int("Path Line Size #PathLineSize", 1, 10, g_menu.routetool.lineSize, 50);
		zgui::text("Path Default");
		zgui::colorpicker("#PathDefault", g_menu.routetool.colors.pathDefault);
		zgui::text("Path Lost Speed");
		zgui::colorpicker("#PathLost", g_menu.routetool.colors.pathLostSpeed);
		zgui::text("Path OnGround");
		zgui::colorpicker("#PathOnGround", g_menu.routetool.colors.pathOnGround);
		zgui::text("Path Crouched");
		zgui::colorpicker("#PathOnCrouch", g_menu.routetool.colors.pathOnCrouch);
	}
	zgui::end_groupbox();
}


void c_menu::MiscTab()
{
	zgui::next_column(50, 0);
	zgui::begin_groupbox("", { 260, 320 });
	{
		zgui::checkbox("Scroll graph #ScrollGraph", g_menu.scrollgraph.enabled);

		zgui::checkbox("Velocity graph #VelocityGraph", g_menu.velocitygraph.enabled);
	}
	zgui::end_groupbox();

	zgui::next_column(270, 0);
	zgui::begin_groupbox("", { 260, 320 }, 0);
	{

	}
	zgui::end_groupbox();
}