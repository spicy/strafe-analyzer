#pragma once
#include <string>
#include "../SDK+/Color.h"
#include "zgui.hh"
#include "../Analyzer/AnalyzerEnums.h"

class c_menu
{
public:
	void Render(std::string game);

	///////// VARS /////////
	bool menuOpened;

	struct 
	{
		// strafetrainer
		color perf = { 255, 255, 255, 120 },
			synced = { 61, 79, 115, 255 },
			notSynced = { 216, 162, 55, 255 },
			counterStrafe = { 0, 0, 0, 255 },
			lostSpeed = { 250, 75, 75, 255 };

		// synctrainer
		color left = { 61, 79, 115, 255 },
			  right = { 216, 162, 55, 255 };

		// routetool
		color pathDefault = { 61, 79, 115, 255 },
			pathLostSpeed = { 250, 75, 75, 255 },
			pathOnGround = { 216, 162, 55, 255 },
			pathOnCrouch = { 250, 75, 75, 255 };

		// misc
		color bg = { 8, 11, 16, 255 };
	} colors;

	int gamemode = 0;

	struct 
	{
		bool mainMenu = true, 
			servers = false,
			strafeTrainer = false,
			keys = false,
			routetool = false,
			misc = false;
	} tabs;

	struct 
	{
		bool enabled = false;
		bool smooth = true;
		bool strafeTrainerStats = false;
		bool invertDir = false;

		int dataWidth = 6;
		int dataHeight = 10;
		int	historySize = 85;
		float speedLossTolerance = 0.01f;
		int lineSize = 3;

		bool centered = true;
		bool paused = false;

		int xOffset = 300;
		int yOffset = 700;
		int graphType = 0;

		struct {
			zgui::color perfColor = { 255, 255, 255, 120 };
			zgui::color synced = { 61, 79, 115, 255 }; //13, 136, 131
			zgui::color notSynced = { 216, 162, 55, 255 };
			zgui::color counterStrafe = { 0, 0, 0, 255 };
			zgui::color lostSpeed = { 250, 75, 75, 255 }; //make different later?
		}colors;
	} strafetrainer;

	struct 
	{
		bool enabled = false;
		bool statistics = false;

		int strafeHistorySize = 8;

		struct
		{
			zgui::color leftDir = { 79, 116, 168, 255 };
			zgui::color rightDir = { 237, 229, 142, 255 };
		}colors;
	} synctrainer;

	struct 
	{
		bool enabled = false;
		bool centered = true;
	} scrollgraph;

	struct
	{
		bool enabled = false;
		bool centered = true;
	} velocitygraph;

	struct
	{
		struct
		{
			bool enabled = false;
			std::string menuText = "Record a replay!";
		} menu;

		struct
		{
			bool enabled = false;
			int pathType = 0;
		} draw;

		struct
		{
			zgui::color pathDefault = { 61, 79, 115, 255 },
				pathLostSpeed = { 250, 75, 75, 255 },
				pathOnGround = { 216, 162, 55, 255 },
				pathOnCrouch = { 250, 75, 75, 255 };
		} colors;

		bool recording = false;
		bool hasRunRecorded = false;
		bool showSpeedLoss = false;
		int firstTickJumped = 0;
		int drawDistance = 600;
		int lineSize = 6;
	} routetool;

private:
	void MainMenuTab();

	void ServersTab();

	void StrafeTrainerTab();

	void KeysTab();

	void RouteToolTab();

	void MiscTab();

	enum
	{
		check_box,
		slider,
		combo_box,
		multi_box
	};
};

extern c_menu g_menu;
