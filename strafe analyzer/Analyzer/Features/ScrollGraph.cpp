#include "scrollGraph.h"

#include "../History.h"
#include "../AnalyzerEnums.h"

#include "../../sdk+/sdk.h"
#include "../../zgui/menu.h"
#include "../../sdk+/drawing.h"
#include "../../sdk+/color.h"
#include "../../sdk+/console.h"

namespace ScrollGraph
{
	/// <summary>
	/// Draws the players scrollGraph history
	/// </summary>
	void Paint()
	{
        if (!g_menu.scrollgraph.enabled) return;

        const int DATA_WIDTH = g_menu.strafetrainer.dataWidth;
        const int HISTORY_SIZE = History::tickHist.size();
        int X_OFF = g_menu.strafetrainer.xOffset;
        const int Y_OFF = g_menu.strafetrainer.yOffset;

        int screenWidth, screenHeight;
        Interfaces::engine->get_screen_size(screenWidth, screenHeight);

        int xCenter = (screenWidth / 2);

        if (g_menu.scrollgraph.centered)
        {
            X_OFF = xCenter - ((HISTORY_SIZE * DATA_WIDTH) / 2);
        }

        render::filled_rect(X_OFF - 10, Y_OFF - 10, ((HISTORY_SIZE - 1) * DATA_WIDTH) + 25, 40, {76, 82, 92, 110});

        color scrollStateColor{ 0, 0, 0, 255 };
        for (int i = HISTORY_SIZE - 1; i >= 0; i--)
        {
            switch (History::tickHist[i].scrolling)
            {
            case 0:
                scrollStateColor = g_menu.colors.synced;
                break;
            case 1:
                scrollStateColor = g_menu.colors.notSynced;
                break;
            }

            render::filled_rect(X_OFF + i * DATA_WIDTH, Y_OFF + 10, DATA_WIDTH, 10, scrollStateColor);

            if (!(History::tickHist[i].posType == PositionType::AIR))
            {
                render::filled_rect(X_OFF + i * DATA_WIDTH, Y_OFF, DATA_WIDTH, 10, g_menu.colors.perf);
            }
        }
	}
}