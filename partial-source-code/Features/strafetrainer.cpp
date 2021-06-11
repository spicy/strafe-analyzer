#include "Strafetrainer.h"
#include "../AnalyzerInlines.h"
#include "../DrawUtil.h"

#include "../../zgui/Menu.h"
#include "../../SDK+/SDK.h"

namespace StrafeTrainer
{
    /// <summary>
    /// Draws a graph onto the players screen using the History vector
    /// </summary>
    void Paint()
    {
        if (!History::tickHist.size() > 1) return;
        if (!g_menu.strafetrainer.enabled) return;

        const int DATA_WIDTH = g_menu.strafetrainer.dataWidth;
        const int HISTORY_SIZE = History::tickHist.size();
        const float MAX_ANGLE = 20.0f;

        int screenWidth, screenHeight;
        Interfaces::engine->get_screen_size(screenWidth, screenHeight);

        // Find the correct graph Offset based on menuoptions
        int xOffset = g_menu.strafetrainer.xOffset;
        int yOffset = g_menu.strafetrainer.yOffset;

        int xCenter = (screenWidth / 2);

        if (g_menu.strafetrainer.centered)
        {
            xOffset = xCenter - ((HISTORY_SIZE * DATA_WIDTH) / 2);
        }

        StrafeTrainerGraphType graph = static_cast<StrafeTrainerGraphType>(g_menu.strafetrainer.graphType);
        if (graph == StrafeTrainerGraphType::GRAPH_FILLED)
        {
            // draw PerfYaw
            DrawUtil::PaintFilledGraph(History::tickHist.begin(), History::tickHist.end(),
                xOffset, yOffset, MAX_ANGLE, false, g_menu.colors.perf, 
                [](auto i) { return i.perfDeltaYaw; });
            // and deltaYaw
            DrawUtil::PaintFilledGraph(History::tickHist.begin(), History::tickHist.end(),
                xOffset, yOffset, MAX_ANGLE, true, g_menu.colors.synced,
                [](auto i) { return i.deltaYaw; });
        }
        else if (graph == StrafeTrainerGraphType::GRAPH_LINE)
        {
            // draw PerfYaw
            DrawUtil::PaintLineGraph(History::tickHist.begin(), History::tickHist.end(), xOffset, yOffset, MAX_ANGLE,
                false, g_menu.colors.perf, g_menu.strafetrainer.lineSize, 
                [](auto i) { return i.perfDeltaYaw; });
            // and deltaYaw
            DrawUtil::PaintLineGraph(History::tickHist.begin(), History::tickHist.end(), xOffset, yOffset, MAX_ANGLE,
                true, g_menu.colors.synced, g_menu.strafetrainer.lineSize,
                [](auto i) { return i.deltaYaw; });
        }
        else if (graph == StrafeTrainerGraphType::GRAPH_HORIZONTAL)
        {
            int yOff = 600;
            DrawUtil::PaintHorizontalGraph(History::tickHist.data(), &TickData::perfDeltaYaw, &TickData::deltaYaw,
                                            500, xCenter, yOff, true, color::white(200));
        }
        else if (graph == StrafeTrainerGraphType::GRAPH_VERTICAL)
        {
            int xOff = (screenWidth / 2) - 20;
            int yOff = 500;
            DrawUtil::PaintVerticalGraph(History::tickHist.data(), &TickData::perfDeltaYaw, &TickData::deltaYaw,
                                        500, 6, xOff, yOff, true, color::white(200));
        }
    }
}