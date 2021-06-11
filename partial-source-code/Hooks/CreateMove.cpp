#include "../sdk+/console.h"
#include "hooks.h"

#include "../Analyzer/AnalyzerMath.h"
#include "../Analyzer/AnalyzerInlines.h"

#include "../Analyzer/Features/TickHistory.h"
#include "../Analyzer/Features/SyncTrainer.h"
#include "../Analyzer/Features/ScrollGraph.h"
#include "../Analyzer/Features/RouteTool.h"
#include "../Analyzer/Features/VelocityGraph.h"

bool __fastcall Hooks::CreateMove::Hook(void* ecx, void* edx, float input_sample_frame_time, CUserCmd* cmd) 
{
	CreateMove_original(input_sample_frame_time, cmd);

	if (!cmd || !cmd->command_number())
	{
		return CreateMove_original(input_sample_frame_time, cmd);
	}

	player = reinterpret_cast<player_t*>(Interfaces::ent_list->get_client_entity(Interfaces::engine->get_local_player()));

	if (!g_menu.strafetrainer.paused)
	{
		// Update tick history
		TickHistory::Update(cmd);

		SyncTrainer::Update();
		RouteTool::Update();
	}

	return false;
}