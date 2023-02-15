//#include "../analyzer/config.h"
#include "../Interfaces/Interfaces.h"
#include "../sdk+/drawing.h"
#include "../sdk+/fnv1.h"
#include "../sdk+/utils.hpp"
#include "../zgui/zgui.hh"
#include "../zgui/menu.h"
#include "hooks.h"

#include "../sdk+/console.h"

#include "../Analyzer/Features/StrafeTrainer.h"
#include "../Analyzer/Features/SyncTrainer.h"
#include "../Analyzer/Features/ScrollGraph.h"
#include "../Analyzer/Features/RouteTool.h"
#include "../Analyzer/Features/VelocityGraph.h"

void __stdcall Hooks::PaintTraverse::Hook(unsigned int panel, bool force_repaint, bool allow_force) 
{
	auto panel_to_draw = fnv::hash(Interfaces::panel->get_panel_name(panel));
	PaintTraverse_original(Interfaces::panel, panel, force_repaint, allow_force);

	switch (panel_to_draw){
	case fnv::hash("MatSystemTopPanel"):
	{
		StrafeTrainer::Paint();
		SyncTrainer::Paint();
		ScrollGraph::Paint();
		VelocityGraph::Paint();
		RouteTool::Paint();
	}

	case fnv::hash("FocusOverlayPanel"):
	{
		// Renders the menu based on enabled TABS
		g_menu.Render(game.c_str());
		Interfaces::input->enable_input(!menu_open);
	}
	default:;
	}
}