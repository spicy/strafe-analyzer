#pragma once
#include <vector>
#include <string>

enum class MouseDir
{
	LEFT = -1,
	NONE,
	RIGHT
};

enum class KeyDir
{
	LEFT = -1,
	NONE,
	RIGHT,
	FORWARD,
	FORWARD_LEFT,
	FORWARD_RIGHT,
	BACK,
	BACK_LEFT,
	BACK_RIGHT,
	COUNTER_STRAFE
};

enum class PositionType
{
	GROUND = 0,
	AIR
};

enum class SyncType
{
	COUNTERSTRAFE = 0,
	SYNCED,
	NOT_SYNCED
};

enum class StrafeTrainerGraphType
{
	GRAPH_FILLED = 0,
	GRAPH_LINE,
	GRAPH_HORIZONTAL,
	GRAPH_VERTICAL,
	GRAPH_COUNT
};

enum class RouteToolGraphType
{
	GRAPH_LINE = 0,
	GRAPH_DOT,
	GRAPH_COUNT
};

enum class Gamemodes
{
	BHOP = 0,
	SURF, 
	KZ,
	HNS
};