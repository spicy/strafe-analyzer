#pragma once
#include "SDK+/Sdk.h"

class c_config
{
public:
	c_config();
	void load(const std::string name);
	void save(const std::string name);
	void refresh();

	struct 
	{
		bool unhook = false;
		std::vector<std::string> config_list = { "default" };
		std::string config_name;
		int config_id = 0;
	} csettings;

	std::string directory_path = "C:/StrafeAnalyzer/Config";
};
extern c_config g_config;
