#include "SyncTrainer.h"

#include "../AnalyzerEnums.h"
#include "../AnalyzerInlines.h"
#include "../AnalyzerMath.h"
#include "../History.h"

#include "../../sdk+/sdk.h"
#include "../../zgui/menu.h"
#include "../../sdk+/drawing.h"
#include "../../sdk+/color.h"
#include "../../sdk+/console.h"

#pragma region Templates
template <typename T>
void pop_front(std::vector<T>& v)
{
	if (v.size() > 0)
		v.erase(v.begin());
}

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << a_value;
	return out.str();
}
#pragma endregion

namespace SyncTrainer
{
	void Update()
	{
		if (!g_menu.synctrainer.enabled) return;
		const int CUR_TICK_NUM = History::tickHist.size() - 1;
		const TickData curTick = History::tickHist[CUR_TICK_NUM];

		// Check TickHistory for non NAN latency
		if (curTick.latencyAmount != 999999)
		{
			StrafeData newStrafe;
			newStrafe.strafeNum = curTick.curStrafes;
			newStrafe.jumpNum = curTick.curJumps;
			newStrafe.latencyAmount = curTick.latencyAmount;

			History::strafeHist.push_back(newStrafe);

			// Pop the oldest strafeHist item if it is over the max size
			if (History::strafeHist.size() > g_menu.synctrainer.strafeHistorySize)
			{
				for (int i = 0; i < g_menu.synctrainer.strafeHistorySize - History::strafeHist.size(); i++)
				{
					pop_front(History::strafeHist);
				}
			}
		}
	}

	void Paint()
	{
		if (!g_menu.synctrainer.enabled) return;

		int screenWidth, screenHeight;
		Interfaces::engine->get_screen_size(screenWidth, screenHeight);

		if (History::strafeHist.size() > 0)
		{
			for (int i = 0; i < History::strafeHist.size(); i++)
			{
				color tempColor;

				// Differentiate one strafe from another by changing its color
				if (History::strafeHist[i].jumpNum % 2 == 0) tempColor = g_menu.colors.left;		// Even
				else tempColor = g_menu.colors.right;												// Odd

				const int xPos = (int)(0.75 * screenWidth);

				if (History::strafeHist[i].latencyAmount > 0)
				{
					render::s_text(xPos, 40 + (i * 25), tempColor, render::moon_font, false, "Jump #"
						+ std::to_string(History::strafeHist[i].jumpNum) + " Strafe #" + std::to_string(History::strafeHist[i].strafeNum)
						+ " Late by " + to_string_with_precision(std::fabs(History::strafeHist[i].latencyAmount), 0) + "t");
				}

				else if (History::strafeHist[i].latencyAmount < 0)
				{
					render::s_text(xPos, 40 + (i * 25), tempColor, render::moon_font, false, "Jump #"
						+ std::to_string(History::strafeHist[i].jumpNum) + " Strafe #" + std::to_string(History::strafeHist[i].strafeNum)
						+ " Early by " + to_string_with_precision(std::fabs(History::strafeHist[i].latencyAmount), 0) + "t");
				}

				else if (History::strafeHist[i].latencyAmount == 0)
				{
					render::s_text(xPos, 40 + (i * 25), tempColor, render::moon_font, false, "Jump #"
						+ std::to_string(History::strafeHist[i].jumpNum) + " Strafe #"
						+ std::to_string(History::strafeHist[i].strafeNum) + " Perf!:) ");
				}

				/*
				if (g_menu.synctrainer.statistics)
				{
					render::s_text(xPos, 40 + (History::strafeHist.size() * 25), color::white(255), render::moon_font, false, "Late: " + to_string_with_precision(avgLate, 2));
					render::s_text(xPos, 40 + ((History::strafeHist.size() + 1) * 25), color::white(255), render::moon_font, false, "Early: " + to_string_with_precision(avgEarly, 2));
					render::s_text(xPos, 40 + ((History::strafeHist.size() + 2) * 25), color::white(255), render::moon_font, false, "Perf: " + to_string_with_precision(avgPerf, 2));


					//p = x / float(width - 1)
					//r = int((1.0-p) * r1 + p * r2 + 0.5)
					//g = int((1.0-p) * g1 + p * g2 + 0.5)
					//b = int((1.0-p) * b1 + p * b2 + 0.5)
					color colorLate = color(std::fmin(avgLateLatency * 30, 255), std::fmin(255 - (avgLateLatency * 30), 255), 0, 255);
					color colorEarly = color(std::fmin(avgEarlyLatency * 30, 255), std::fmin(255 - (avgEarlyLatency * 30), 255), 0, 255);

					render::s_text(xPos + 100, 40 + (History::strafeHist.size() * 25), color::white(255), render::moon_font, false, "Avg Latency: " + to_string_with_precision(avgLateLatency, 2));
					render::s_text(xPos + 100, 40 + ((History::strafeHist.size() + 1) * 25), color::white(255), render::moon_font, false, "Avg Latency: " + to_string_with_precision(avgEarlyLatency, 2));
				}
				*/
			}
		}
	}
}