#pragma once
#include "../sdk+/sdk.h"

#include "AnalyzerEnums.h"
#include "AnalyzerMath.h"
#include "History.h"

#include "../zgui/zgui.hh"
#include "../SDK+/Color.h"

/// <summary>
/// returns a converted zcolor->color
/// </summary>
inline color zColorToColor(zgui::color zcolor)
{
    return { zcolor.r, zcolor.g, zcolor.b, zcolor.a };
}

/// <summary>
/// Checks if the players keypresses are synced with their mouse movements.
/// </summary>
/// <returns> 0 = counterstrafing, 1 = synced, 2 = not synced </returns>
inline SyncType GetSyncState(int currentButtons, MouseDir mouseDir)
{
    if (game_engine == ENGINE_CSGO)
    {
        if (!player->is_alive()) return SyncType::SYNCED;
    }

    if (currentButtons & in_moveleft && currentButtons & in_moveright || currentButtons & in_forward && currentButtons & in_back)
    {
        return SyncType::COUNTERSTRAFE;
    }

    else if ((mouseDir == MouseDir::RIGHT && currentButtons & in_moveright) || (mouseDir == MouseDir::LEFT && currentButtons & in_moveleft))
    {
        return SyncType::SYNCED;
    }

    else return SyncType::NOT_SYNCED;
}

/// <summary>
/// Checks if the player lost speed compared to the previous tick.
/// </summary>
/// <returns> Returns true if the player lost speed on the current tick. </returns>
inline bool HasLostSpeed(float tolerance, double curSpeed)
{
    const int PREV_TICK = History::tickHist.size() - 2;

    // if lost speed, diff is negative
    double diff = curSpeed - History::tickHist[PREV_TICK].speed;
    return (diff < -tolerance);
}

/// <summary>
/// Checks if the player jumped compared to the previous tick.
/// </summary>
/// <returns> Returns true if the player just jumped this tick </returns>
inline bool HasJumped()
{
    const int PREV_TICK = History::tickHist.size() - 2;
    return (player->is_in_air()) && (History::tickHist[PREV_TICK].posType == PositionType::GROUND);
}

/// <summary>
/// Player has been on ground for more than one tick
/// </summary>
inline bool HasBeenOnGround(int currentTick)
{
    if (currentTick <= 1 || currentTick >= History::tickHist.size()) return false;
    return (History::tickHist[currentTick].posType == PositionType::GROUND) && (History::tickHist[currentTick - 1].posType == PositionType::GROUND);
}

/// <summary>
/// Checks if the player changed their strafe direction compared to the previous tick.
/// </summary>
/// <returns> Returns true if the player changed strafe directions </returns>
inline bool HasStrafed(MouseDir mouseDir, KeyDir keyDir, MouseDir strafeDir)
{
    int iMouseDir = static_cast<int>(mouseDir);
    int iKeyDir = static_cast<int> (keyDir);
    int iStrafeDir = static_cast<int>(strafeDir);

    // (iKeyDir != iStrafeDir)
    
    return (iMouseDir != iStrafeDir)
        && fabs(MouseAndKeyPhiDiff(strafeDir, keyDir)) > (M_PI / 2)
        && (iKeyDir != 0 && iStrafeDir != 0 && iMouseDir != 0);
}

/// <summary>
/// Gets the number of ticks that the player was unsynced (or none)
/// </summary>
/// <returns> Returns a negative value if the player pressed their key too early, positive if too late, zero = perfect </returns>
inline int GetSyncLatency(MouseDir eStrafeDir)
{
    int mouseIndex = 0, keyIndex = 0;

    // starts at the current tick in the History vector. Loops back until key/mouse is equal to the strafeDir 
    // IDEA: if the current tick is non movement or counterstrafing then add to a counter?

    // increments mouseI until it finds a previous tick where mouseDir is equal to strafeDir
    for (int i = History::tickHist.size() - 1; (History::tickHist[i].mouseDir == eStrafeDir
        || History::tickHist[i].mouseDir == MouseDir::NONE) && i > 0; i--)
    {
        mouseIndex++;
    }
    // increments keyI until it finds a previous tick where keyDir is equal to strafeDir
    for (int i = History::tickHist.size() - 1; (static_cast<int>(History::tickHist[i].keyDir) == static_cast<int>(eStrafeDir)
        || History::tickHist[i].keyDir == KeyDir::NONE) && i > 0; i--)
    {
        keyIndex++;
    }

    return mouseIndex - keyIndex;
}