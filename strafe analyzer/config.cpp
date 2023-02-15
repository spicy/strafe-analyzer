#ifndef CONFIG_H 
#define CONFIG_H 
#include "config.h"
#endif

#include "nlohmann/json.hpp"
#include <Windows.h>
#include <filesystem>
#include <iostream>
#include <fstream>

using jsonf = nlohmann::json;

c_config::c_config()
{
	if (!std::filesystem::exists(directory_path))
		std::filesystem::create_directories(directory_path);

	refresh();
}

void c_config::refresh()
{
	g_config.csettings.config_list.clear();

	for (const auto& entry : std::filesystem::directory_iterator(directory_path))
		if (entry.path().string().find(".json"))
		{
			const auto length = entry.path().string().erase(0, 18).length();
			g_config.csettings.config_list.emplace_back(entry.path().string().erase(0, 18).erase(length - 5, 5));
		}

	if (g_config.csettings.config_list.empty())
	{
		save("default.json");
		refresh();
	}
}

void c_config::save(const std::string name)
{
	const auto path = directory_path + "/" + name;

	std::ofstream out(path);

	if (!out.is_open())
	{
		return;
	}

	jsonf j;

	////////////////////////////////////////////////////////////////////////////////////////////////DELETE ALL AND REDO SINCE BAD VAR NAMES
	/*
	j["Spicy - Config"]["strafetrainer"]["StrafeTrainer"] = g_Menu.strafetrainer.strafeTrainer;
	j["Spicy - Config"]["strafetrainer"]["StrafeTrainerStats"] = g_Menu.strafetrainer.strafeTrainerStats;
	j["Spicy - Config"]["strafetrainer"]["StrafeDelta"] = g_Menu.strafetrainer.strafeDelta;
	j["Spicy - Config"]["strafetrainer"]["DataHeight"] = g_Menu.strafetrainer.dataHeight;
	j["Spicy - Config"]["strafetrainer"]["DataWidth"] = g_Menu.strafetrainer.dataWidth;
	j["Spicy - Config"]["strafetrainer"]["GraphStyle"] = g_Menu.strafetrainer.GraphStyle;
	j["Spicy - Config"]["strafetrainer"]["historySize"] = g_Menu.strafetrainer.historySize;
	j["Spicy - Config"]["strafetrainer"]["yScaling"] = g_Menu.strafetrainer.yScaling;
	j["Spicy - Config"]["strafetrainer"]["smooth"] = g_Menu.strafetrainer.smooth;
	j["Spicy - Config"]["strafetrainer"]["VelocityGraph"] = g_Menu.misc.velocityGraph;

	j["Spicy - Config"]["strafetrainer"]["colors"]["STCounterStrafe"]["r"] = g_Menu.strafetrainer.colors.counterStrafe.r;
	j["Spicy - Config"]["strafetrainer"]["colors"]["STCounterStrafe"]["g"] = g_Menu.strafetrainer.colors.counterStrafe.g;
	j["Spicy - Config"]["strafetrainer"]["colors"]["STCounterStrafe"]["b"] = g_Menu.strafetrainer.colors.counterStrafe.b;
	j["Spicy - Config"]["strafetrainer"]["colors"]["STCounterStrafe"]["a"] = g_Menu.strafetrainer.colors.counterStrafe.a;
	j["Spicy - Config"]["strafetrainer"]["colors"]["STNotSynced"]["r"] = g_Menu.strafetrainer.colors.notSynced.r;
	j["Spicy - Config"]["strafetrainer"]["colors"]["STNotSynced"]["g"] = g_Menu.strafetrainer.colors.notSynced.g;
	j["Spicy - Config"]["strafetrainer"]["colors"]["STNotSynced"]["b"] = g_Menu.strafetrainer.colors.notSynced.b;
	j["Spicy - Config"]["strafetrainer"]["colors"]["STNotSynced"]["a"] = g_Menu.strafetrainer.colors.notSynced.a;
	j["Spicy - Config"]["strafetrainer"]["colors"]["STSynced"]["r"] = g_Menu.strafetrainer.colors.synced.r;
	j["Spicy - Config"]["strafetrainer"]["colors"]["STSynced"]["g"] = g_Menu.strafetrainer.colors.synced.g;
	j["Spicy - Config"]["strafetrainer"]["colors"]["STSynced"]["b"] = g_Menu.strafetrainer.colors.synced.b;
	j["Spicy - Config"]["strafetrainer"]["colors"]["STSynced"]["a"] = g_Menu.strafetrainer.colors.synced.a;
	j["Spicy - Config"]["strafetrainer"]["colors"]["STperfColor"]["r"] = g_Menu.strafetrainer.colors.perfColor.r;
	j["Spicy - Config"]["strafetrainer"]["colors"]["STperfColor"]["g"] = g_Menu.strafetrainer.colors.perfColor.g;
	j["Spicy - Config"]["strafetrainer"]["colors"]["STperfColor"]["b"] = g_Menu.strafetrainer.colors.perfColor.b;
	j["Spicy - Config"]["strafetrainer"]["colors"]["STperfColor"]["a"] = g_Menu.strafetrainer.colors.perfColor.a;
	j["Spicy - Config"]["strafetrainer"]["colors"]["colorLostSpeed"]["r"] = g_Menu.strafetrainer.colors.lostSpeed.r;
	j["Spicy - Config"]["strafetrainer"]["colors"]["colorLostSpeed"]["g"] = g_Menu.strafetrainer.colors.lostSpeed.g;
	j["Spicy - Config"]["strafetrainer"]["colors"]["colorLostSpeed"]["b"] = g_Menu.strafetrainer.colors.lostSpeed.b;
	j["Spicy - Config"]["strafetrainer"]["colors"]["colorLostSpeed"]["a"] = g_Menu.strafetrainer.colors.lostSpeed.a;


	j["Spicy - Config"]["keys"]["Keypress"] = g_Menu.keys.keypress;
	j["Spicy - Config"]["keys"]["KeypressHistory"] = g_Menu.keys.keypressHistory;
	j["Spicy - Config"]["keys"]["KeypressStats"] = g_Menu.keys.keypressStats;
	j["Spicy - Config"]["keys"]["Showkeys"] = g_Menu.keys.showkeys;
	j["Spicy - Config"]["keys"]["STKeyDir"] = g_Menu.keys.keyDirIndicator;
	j["Spicy - Config"]["keys"]["STMouseDir"] = g_Menu.keys.mouseDirIndicator;
	j["Spicy - Config"]["keys"]["TempoTrainer"] = g_Menu.keys.tempoTrainer;

	j["Spicy - Config"]["keys"]["colors"]["STLeft"]["r"] = g_Menu.keys.colors.leftDir.r;
	j["Spicy - Config"]["keys"]["colors"]["STLeft"]["g"] = g_Menu.keys.colors.leftDir.g;
	j["Spicy - Config"]["keys"]["colors"]["STLeft"]["b"] = g_Menu.keys.colors.leftDir.b;
	j["Spicy - Config"]["keys"]["colors"]["STLeft"]["a"] = g_Menu.keys.colors.leftDir.a;
	j["Spicy - Config"]["keys"]["colors"]["STRight"]["r"] = g_Menu.keys.colors.rightDir.r;
	j["Spicy - Config"]["keys"]["colors"]["STRight"]["g"] = g_Menu.keys.colors.rightDir.g;
	j["Spicy - Config"]["keys"]["colors"]["STRight"]["b"] = g_Menu.keys.colors.rightDir.b;
	j["Spicy - Config"]["keys"]["colors"]["STRight"]["a"] = g_Menu.keys.colors.rightDir.a;


	j["Spicy - Config"]["misc"]["DeadzoneDelta"] = g_Menu.misc.deadzoneDelta;
	j["Spicy - Config"]["misc"]["DeadzoneType"] = g_Menu.misc.deadzoneType;
	j["Spicy - Config"]["misc"]["JumpPrediction"] = g_Menu.misc.jumpPrediction;
	j["Spicy - Config"]["misc"]["IntendedDirection"] = g_Menu.misc.intendedDirection;
	j["Spicy - Config"]["misc"]["Deadzone"] = g_Menu.misc.deadzoneIndicator;
	j["Spicy - Config"]["misc"]["StrafeAmount"] = g_Menu.misc.strafeAmount;
	j["Spicy - Config"]["misc"]["StrafeRange"] = g_Menu.misc.strafeRange;
	j["Spicy - Config"]["misc"]["RecordBot"] = g_Menu.misc.recordBot;
	j["Spicy - Config"]["misc"]["ShowAngles"] = g_Menu.misc.showAngles;


	j["Spicy - Config"]["misc"]["colors"]["VelocityAngle"]["r"] = g_Menu.misc.colors.velocityAngle.r;
	j["Spicy - Config"]["misc"]["colors"]["VelocityAngle"]["g"] = g_Menu.misc.colors.velocityAngle.g;
	j["Spicy - Config"]["misc"]["colors"]["VelocityAngle"]["b"] = g_Menu.misc.colors.velocityAngle.b;
	j["Spicy - Config"]["misc"]["colors"]["VelocityAngle"]["a"] = g_Menu.misc.colors.velocityAngle.a;
	*/
	out << j;
}

void c_config::load(const std::string name)
{
	const auto path = directory_path + "/" + name;

	std::ifstream in(path);

	if (!in.good())
	{
		save(name);
	}

	if (!in.is_open())
	{
		return;
	}

	// read JSON file
	std::ifstream i(path + ".json");
	jsonf j;
	i >> j;
	/*
	g_Menu.strafetrainer.strafeTrainer = j["Spicy - Config"]["strafetrainer"]["StrafeTrainer"];
	g_Menu.strafetrainer.strafeTrainerStats = j["Spicy - Config"]["strafetrainer"]["StrafeTrainerStats"];
	g_Menu.strafetrainer.strafeDelta = j["Spicy - Config"]["strafetrainer"]["StrafeDelta"];
	g_Menu.strafetrainer.dataHeight = j["Spicy - Config"]["strafetrainer"]["DataHeight"];
	g_Menu.strafetrainer.dataWidth = j["Spicy - Config"]["strafetrainer"]["DataWidth"];
	g_Menu.strafetrainer.GraphStyle = j["Spicy - Config"]["strafetrainer"]["GraphStyle"];
	g_Menu.strafetrainer.historySize = j["Spicy - Config"]["strafetrainer"]["historySize"];
	g_Menu.strafetrainer.yScaling = j["Spicy - Config"]["strafetrainer"]["yScaling"];
	g_Menu.strafetrainer.smooth = j["Spicy - Config"]["strafetrainer"]["smooth"];
	g_Menu.misc.velocityGraph = j["Spicy - Config"]["misc"]["VelocityGraph"];

	g_Menu.strafetrainer.colors.counterStrafe.r = j["Spicy - Config"]["strafetrainer"]["colors"]["counterStrafe"]["r"];
	g_Menu.strafetrainer.colors.counterStrafe.g = j["Spicy - Config"]["strafetrainer"]["colors"]["counterStrafe"]["g"];
	g_Menu.strafetrainer.colors.counterStrafe.b = j["Spicy - Config"]["strafetrainer"]["colors"]["counterStrafe"]["b"];
	g_Menu.strafetrainer.colors.counterStrafe.a = j["Spicy - Config"]["strafetrainer"]["colors"]["counterStrafe"]["a"];
	g_Menu.strafetrainer.colors.notSynced.r = j["Spicy - Config"]["strafetrainer"]["colors"]["notSynced"]["r"];
	g_Menu.strafetrainer.colors.notSynced.g = j["Spicy - Config"]["strafetrainer"]["colors"]["notSynced"]["g"];
	g_Menu.strafetrainer.colors.notSynced.b = j["Spicy - Config"]["strafetrainer"]["colors"]["notSynced"]["b"];
	g_Menu.strafetrainer.colors.notSynced.a = j["Spicy - Config"]["strafetrainer"]["colors"]["notSynced"]["a"];
	g_Menu.strafetrainer.colors.synced.r = j["Spicy - Config"]["strafetrainer"]["colors"]["synced"]["r"];
	g_Menu.strafetrainer.colors.synced.g = j["Spicy - Config"]["strafetrainer"]["colors"]["synced"]["g"];
	g_Menu.strafetrainer.colors.synced.b = j["Spicy - Config"]["strafetrainer"]["colors"]["synced"]["b"];
	g_Menu.strafetrainer.colors.synced.a = j["Spicy - Config"]["strafetrainer"]["colors"]["synced"]["a"];
	g_Menu.strafetrainer.colors.perfColor.r = j["Spicy - Config"]["strafetrainer"]["colors"]["perfColor"]["r"];
	g_Menu.strafetrainer.colors.perfColor.g = j["Spicy - Config"]["strafetrainer"]["colors"]["perfColor"]["g"];
	g_Menu.strafetrainer.colors.perfColor.b = j["Spicy - Config"]["strafetrainer"]["colors"]["perfColor"]["b"];
	g_Menu.strafetrainer.colors.perfColor.a = j["Spicy - Config"]["strafetrainer"]["colors"]["perfColor"]["a"];
	g_Menu.strafetrainer.colors.lostSpeed.r = j["Spicy - Config"]["strafetrainer"]["colors"]["lostSpeed"]["r"];
	g_Menu.strafetrainer.colors.lostSpeed.g = j["Spicy - Config"]["strafetrainer"]["colors"]["lostSpeed"]["g"];
	g_Menu.strafetrainer.colors.lostSpeed.b = j["Spicy - Config"]["strafetrainer"]["colors"]["lostSpeed"]["b"];
	g_Menu.strafetrainer.colors.lostSpeed.a = j["Spicy - Config"]["strafetrainer"]["colors"]["lostSpeed"]["a"];

	g_Menu.keys.keypress = j["Spicy - Config"]["keys"]["Keypress"];
	g_Menu.keys.keypressHistory = j["Spicy - Config"]["keys"]["KeypressHistory"];
	g_Menu.keys.keypressStats = j["Spicy - Config"]["keys"]["KeypressStats"];
	g_Menu.keys.showkeys = j["Spicy - Config"]["keys"]["Showkeys"];
	g_Menu.keys.keyDirIndicator = j["Spicy - Config"]["keys"]["KeyDirIndicator"];
	g_Menu.keys.mouseDirIndicator = j["Spicy - Config"]["keys"]["MouseDirIndicator"];
	g_Menu.keys.tempoTrainer = j["Spicy - Config"]["keys"]["TempoTrainer"];

	g_Menu.keys.colors.leftDir.r = j["Spicy - Config"]["keys"]["colors"]["STLeft"]["r"];
	g_Menu.keys.colors.leftDir.g = j["Spicy - Config"]["keys"]["colors"]["STLeft"]["g"];
	g_Menu.keys.colors.leftDir.b = j["Spicy - Config"]["keys"]["colors"]["STLeft"]["b"];
	g_Menu.keys.colors.leftDir.a = j["Spicy - Config"]["keys"]["colors"]["STLeft"]["a"];
	g_Menu.keys.colors.rightDir.r = j["Spicy - Config"]["keys"]["colors"]["STRight"]["r"];
	g_Menu.keys.colors.rightDir.g = j["Spicy - Config"]["keys"]["colors"]["STRight"]["g"];
	g_Menu.keys.colors.rightDir.b = j["Spicy - Config"]["keys"]["colors"]["STRight"]["b"];
	g_Menu.keys.colors.rightDir.a = j["Spicy - Config"]["keys"]["colors"]["STRight"]["a"];


	g_Menu.misc.deadzoneDelta = j["Spicy - Config"]["misc"]["DeadzoneDelta"];
	g_Menu.misc.deadzoneType = j["Spicy - Config"]["misc"]["DeadzoneType"];
	g_Menu.misc.jumpPrediction = j["Spicy - Config"]["misc"]["JumpPrediction"];
	g_Menu.misc.intendedDirection = j["Spicy - Config"]["misc"]["IntendedDirection"];
	g_Menu.misc.deadzoneIndicator = j["Spicy - Config"]["misc"]["Deadzone"];
	g_Menu.misc.strafeAmount = j["Spicy - Config"]["misc"]["StrafeAmount"];
	g_Menu.misc.strafeRange = j["Spicy - Config"]["misc"]["StrafeRange"];
	g_Menu.misc.recordBot = j["Spicy - Config"]["misc"]["RecordBot"];
	g_Menu.misc.showAngles = j["Spicy - Config"]["misc"]["ShowAngles"];


	g_Menu.misc.colors.velocityAngle.r = j["Spicy - Config"]["misc"]["colors"]["VelocityAngle"]["r"];
	g_Menu.misc.colors.velocityAngle.g = j["Spicy - Config"]["misc"]["colors"]["VelocityAngle"]["g"];
	g_Menu.misc.colors.velocityAngle.b = j["Spicy - Config"]["misc"]["colors"]["VelocityAngle"]["b"];
	g_Menu.misc.colors.velocityAngle.a = j["Spicy - Config"]["misc"]["colors"]["VelocityAngle"]["a"];
	*/
	in.close();
}

c_config g_config;