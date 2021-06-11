#pragma once
#include "AnalyzerEnums.h"
#include "../Math/vector3d.h"

struct TickData
{
	//Items comparing 2 ticks
	double deltaYaw = 0;
	int latencyAmount = 0;
	bool lostSpeed = false;

	vec3_t vecViewangles = { 0, 0, 0 };
	vec3_t vecPos = { 0, 0, 0 };
	vec3_t vecVel = { 0, 0, 0 };

	double perfDeltaYaw = 0;
	double speed = 0;

	bool scrolling = false;
	bool crouching = false;

	// Misc
	MouseDir mouseDir = MouseDir::NONE;
    MouseDir strafeDir = MouseDir::NONE;
	KeyDir keyDir = KeyDir::NONE;

	SyncType syncState = SyncType::NOT_SYNCED;
	PositionType posType = PositionType::AIR;

	// Number of jumps / strafes in current "run"
	int curJumps = 0;
	int curStrafes = 0;
};