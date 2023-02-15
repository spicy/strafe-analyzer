#include "hooks.h"
#include "../Servers.h"


void OnConnectToServer(int ip, int connectionPort, int queryPort)
{
	/*
	bool onLan = (Interfaces::convar->get_convar("sv_lan")->get_float(game_engine) == 1) ? true : false;
	bool onAllowedServer = false;

	unsigned char ipBytes[4];
	ipBytes[0] = ip & 0xFF;
	ipBytes[1] = (ip >> 8) & 0xFF;
	ipBytes[2] = (ip >> 16) & 0xFF;
	ipBytes[3] = (ip >> 24) & 0xFF;

	std::string connectedIP = std::to_string(ipBytes[0]) + "." + std::to_string(ipBytes[1]) + "." + std::to_string(ipBytes[2]) + "." + std::to_string(ipBytes[3]);
	//connected_port = std::to_string(queryPort);

	// Loop through all servers
	for (int i = 0; i < AllowedServers::servers.size(); i++)
	{
		// If our connected ip is in the AllowedServers vector
		if (connectedIP.compare(AllowedServers::servers[i].GetIp()) == 0)
		{
			onAllowedServer = true;
		}
	}

	// If the player is not on a LAN server AND they are not on
	// an allowed server, disconnect
	if (!onLan || !onAllowedServer)
	{
		if (game_engine == ENGINE_CSGO)
		{
			Interfaces::engine->execute_cmd_csgo("disconnect");

			for (int i = 0; i < 10; i++)
			{
				Interfaces::engine->execute_cmd_csgo("say Spicy's Strafe Analyzer is not allowed on this server. Contact the owner!");
			}
		}
		else
		{
			Interfaces::engine->execute_cmd_css("disconnect");

			for (int i = 0; i < 10; i++)
			{
				Interfaces::engine->execute_cmd_csgo("say Spicy's Strafe Analyzer is not allowed on this server. Contact the owner!");
			}
		}
	}
	*/
}

void __stdcall Hooks::GameUI::Hook(const char* game, int IP, int connectionPort, int queryPort) 
{
	GameUI_original(Interfaces::gameui, game, IP, connectionPort, queryPort);

	OnConnectToServer(IP, connectionPort, queryPort);
}