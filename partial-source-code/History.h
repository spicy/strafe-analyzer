#pragma once
#include <vector>
#include "TickData.h"
#include "StrafeData.h"

struct History
{
	// Vector of capped size representing the history of the last X ticks
	static std::vector<TickData> tickHist;

	// Vector of capped size representing the last X strafes
	static std::vector<StrafeData> strafeHist;

	// Vector of uncapped size representing all ticks throughout an entire run
	static std::vector<TickData> recordedRun;
};