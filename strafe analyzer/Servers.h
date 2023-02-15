#pragma once
#include <string>
#include <vector>
#include "Analyzer/AnalyzerEnums.h"

class Server
{
private:
	std::string name = "Uninitialized";
	std::string ip = "Uninitialized";
	std::string port = "Uninitialized";
	Gamemodes gamemode;
	int engine;

public:
	Server(std::string nme, std::string i, std::string prt, Gamemodes gamemod, int eng)
		: name(nme), ip(i), port(prt), gamemode(gamemod), engine(eng) {}

	std::string GetName()
	{
		return name;
	}

	std::string GetIp()
	{
		return ip;
	}

	std::string GetPort()
	{
		return port;
	}

	Gamemodes GetGamemode()
	{
		return gamemode;
	}

	int GetEngine()
	{
		return engine;
	}
};

struct AllowedServers
{
	static std::vector<Server> servers;

	static void Initialize()
	{
		Server lacunaHopsNA("LacunaHops NA", "162.248.92.42", "27015", Gamemodes::BHOP, ENGINE_CSS);
		servers.push_back(lacunaHopsNA);

		Server blankHopsNA("BlankHops NA", "92.38.148.25", "27015", Gamemodes::BHOP, ENGINE_CSS);
		servers.push_back(blankHopsNA);

		Server blankHopsEU("BlankHops EU", "31.186.250.4", "27015", Gamemodes::BHOP, ENGINE_CSS);
		servers.push_back(blankHopsEU);

		Server baguetteEU("Baguette EU", "78.46.80.174", "27215", Gamemodes::BHOP, ENGINE_CSS);
		servers.push_back(baguetteEU);

		Server shizangleNA("[shizangle] T1 / T2 strafe maps", "74.91.120.189", "27015", Gamemodes::BHOP, ENGINE_CSS);
		servers.push_back(shizangleNA);
	}
};
