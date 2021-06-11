#pragma once
#include "VelocityGraph.h"

#include "../History.h"
#include "../AnalyzerEnums.h"
#include "../DrawUtil.h"

#include "../../sdk+/sdk.h"
#include "../../zgui/menu.h"
#include "../../sdk+/drawing.h"
#include "../../sdk+/color.h"

namespace VelocityGraph
{
    /// <summary>
    /// Draws the players velocity graph
    /// </summary>
    void Paint()
    {
        if (!g_menu.velocitygraph.enabled) return;

        const int DATA_WIDTH = g_menu.strafetrainer.dataWidth;
        const int HISTORY_SIZE = History::tickHist.size();
        int X_OFF = g_menu.strafetrainer.xOffset;
        const int Y_OFF = g_menu.strafetrainer.yOffset;

        int screenWidth, screenHeight;
        Interfaces::engine->get_screen_size(screenWidth, screenHeight);

        int xCenter = (screenWidth / 2);

        if (g_menu.velocitygraph.centered)
        {
            X_OFF = xCenter - ((HISTORY_SIZE * DATA_WIDTH) / 2);
        }

        const int MAX_SPEED = 3500;


        // represents the number of units per pixel
        const int DIVISOR = (screenHeight / 2) / MAX_SPEED;
        DrawUtil::PaintLineGraph(History::tickHist.begin(), History::tickHist.end(),
            X_OFF, Y_OFF, 13.0f, true, g_menu.colors.perf, 3,
            [DIVISOR](auto i) { return i.speed / DIVISOR; });
    }
}