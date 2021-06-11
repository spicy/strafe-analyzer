#pragma once
#include "AnalyzerEnums.h"
#include "AnalyzerMath.h"
#include "AnalyzerInlines.h"

#include "../SDK+/Drawing.h"
#include "../SDK+/SDK.h"
#include "../SDK+/color.h"

#include "../zgui/zgui.hh"
#include "../zgui/Menu.h"

namespace DrawUtil
{

#pragma region Coloring
    /// <summary>
    /// Changes colors if the player has lost speed, or if the player has been on 
    /// the ground for at least 2 concurrent ticks
    /// else, it uses the players current Sync State
    /// </summary>
    inline color GetTickColor(int index)
    {
        color curStateColor = { 0, 0, 0 };

        // Player has been on the ground for at least 2 ticks in a row (current)
        if (HasBeenOnGround(index))
        {
            curStateColor = zColorToColor(g_menu.strafetrainer.colors.synced);
        }
        // Lostspeed
        else if (History::tickHist[index].lostSpeed)
        {
            curStateColor = zColorToColor(g_menu.strafetrainer.colors.lostSpeed);
        }
        else
        {
            switch (History::tickHist[index].syncState)
            {
            case SyncType::COUNTERSTRAFE:
                curStateColor = zColorToColor(g_menu.strafetrainer.colors.counterStrafe);
                break;
            case SyncType::SYNCED:
                curStateColor = zColorToColor(g_menu.strafetrainer.colors.synced);
                break;
            case SyncType::NOT_SYNCED:
                curStateColor = zColorToColor(g_menu.strafetrainer.colors.notSynced);
                break;
            }
        }
        return curStateColor;
    }
#pragma endregion

#pragma region Graphs

    template <class IT, class F>
    inline void PaintFilledGraph(IT beginning, IT end, int xOffset, int yOffset,
        double maxAngle, bool colorWithSync, color defaultColor, F functor)
    {
        const int DATA_WIDTH = g_menu.strafetrainer.dataWidth;
        const int DATA_HEIGHT = g_menu.strafetrainer.dataHeight;

        // Create temp color
        color curStateColor{ 0, 0, 0 };
        int endI = std::distance(beginning, end);

        // Create temp iterator and set to the beginning
        IT itIndex = beginning;

        while (itIndex != end)
        {
            int xPos, yPos;
            int i = std::distance(beginning, itIndex);

            if (g_menu.strafetrainer.invertDir) xPos = i * DATA_WIDTH;
            else xPos = (endI - i) * DATA_WIDTH;
            yPos = functor(*itIndex) * DATA_HEIGHT;

            if (functor(*itIndex) < maxAngle)
            {
                if (!colorWithSync) curStateColor = defaultColor;
                else curStateColor = GetTickColor(i);

                render::filled_rect(xOffset + xPos, yOffset - yPos,
                    DATA_WIDTH, yPos, curStateColor);
            }

            itIndex++;
        }
    }


    template <class IT, class F>
    inline void PaintLineGraph(IT beginning, IT end, int xOffset, int yOffset, 
        double maxAngle, bool colorWithSync, color defaultColor, int linePaddingCount, F functor)
    {
        const int DATA_WIDTH = g_menu.strafetrainer.dataWidth;
        const int DATA_HEIGHT = g_menu.strafetrainer.dataHeight;

        // Create temp color
        color curStateColor{ 0, 0, 0 };

        // Create temp iterator and set to the beginning
        IT itIndex = beginning;
        IT nextIndex = std::next(itIndex, 1);

        int endI = std::distance(beginning, end);

        while (nextIndex != end)
        {
            int xPos1, xPos2;
            int i = std::distance(beginning, itIndex);

            if (g_menu.strafetrainer.invertDir)
            {
                xPos1 = i * DATA_WIDTH;
                xPos2 = (i + 1) * DATA_WIDTH;
            }
            else
            {
                xPos1 = (endI - i) * DATA_WIDTH;
                xPos2 = (endI - (i + 1)) * DATA_WIDTH;
            }

            int yPos1 = functor(*itIndex) * DATA_HEIGHT;
            int yPos2 = functor(*nextIndex) * DATA_HEIGHT;

            if (functor(*itIndex) < maxAngle && functor(*nextIndex) < maxAngle)
            {
                if (!colorWithSync) curStateColor = defaultColor;
                else curStateColor = GetTickColor(i);

                // Padding lines
                for (int j = 0; j < linePaddingCount; j++)
                {
                    render::line(xOffset + xPos1, yOffset - yPos1 + j,
                        xOffset + xPos2, yOffset - yPos2 + j, curStateColor);
                }
            }

            itIndex++;
            nextIndex++;
        }
    }


    template <class T, class T2, class S>
    inline void PaintHorizontalGraph(T* vecPtr, T2 S::* targetElem1Ptr, T2 S::* targetElem2Ptr,
        int desiredPixels, int xCenter, int yOffset, bool colorWithSync, color borderColor)
    {
        const int CUR_TICK = History::tickHist.size() - 1;
        color curStateColor = { 0,0,0 };

        const double maxAngle = vecPtr[CUR_TICK].*targetElem1Ptr * 2;
        const double anglePerPixel = maxAngle / desiredPixels;
        double viewangleX = min(vecPtr[CUR_TICK].*targetElem2Ptr, maxAngle) / anglePerPixel;

        if (!colorWithSync) curStateColor = g_menu.colors.notSynced;
        else curStateColor = GetTickColor(CUR_TICK);

        const int HEIGHT = 50;

        // Draw outer border
        render::rect(xCenter - (desiredPixels / 2) - 1, yOffset - 1, desiredPixels + 5, HEIGHT + 2, borderColor);

        // Draw middle line
        render::line(xCenter, yOffset, xCenter, yOffset + HEIGHT, borderColor);

        // Draw Viewangle
        render::filled_rect(xCenter - (desiredPixels / 2) + viewangleX, yOffset, g_menu.strafetrainer.lineSize, HEIGHT, curStateColor);
    }


    template <class T, class T2, class S>
    inline void PaintVerticalGraph(T* vecPtr, T2 S::* targetElem1Ptr, T2 S::* targetElem2Ptr,
        int desiredPixels, double maxAngle, int xOffset, int yOffset, bool colorWithSync, color borderColor)
    {
        const int DATA_WIDTH = g_menu.strafetrainer.dataWidth;
        const int DATA_HEIGHT = g_menu.strafetrainer.dataHeight;
        const int CUR_TICK = History::tickHist.size() - 1;
        color curStateColor = { 0, 0, 0 };

        // Find the ratio of deltaYaw to perfangle
        const double anglePerPixel = maxAngle / desiredPixels;

        double yPos1 = min(min(vecPtr[CUR_TICK].*targetElem1Ptr, maxAngle) / anglePerPixel, desiredPixels);
        double yPos2 = min(min(vecPtr[CUR_TICK].*targetElem2Ptr, maxAngle) / anglePerPixel, desiredPixels);

        if (!colorWithSync) curStateColor = g_menu.colors.synced;
        else curStateColor = GetTickColor(CUR_TICK);

        const int WIDTH = 40;
        // Draw outer rectangle
        render::rect(xOffset - 1, yOffset - 1, WIDTH + 2, desiredPixels + 5, borderColor);

        // Draw viewangle
        render::filled_rect(xOffset, yOffset + desiredPixels - yPos1, WIDTH, g_menu.strafetrainer.lineSize, g_menu.colors.notSynced);

        // Draw perfAngle
        render::filled_rect(xOffset, yOffset + desiredPixels - yPos2, WIDTH, g_menu.strafetrainer.lineSize, curStateColor);
    }
#pragma endregion
}