#include "TickHistory.h"
#include "../TickData.h"
#include "../History.h"

#include "../AnalyzerInlines.h"
#include "../AnalyzerMath.h"
#include "../../zgui/menu.h"

#ifndef NOLATENCY
#define NOLATENCY 999999;
#endif

template <typename T>
void pop_front(std::vector<T>& v)
{
    if (v.size() > 0)
        v.erase(v.begin());
}

template <class T, class T2, class T3, class S>
double SmoothValueComparedToVector(T value, T2* vecPtr, T3 S::* targetElemPtr, int numElemToAvg)
{
    double smoothed = value;
    // Smooths graph upwards to remove large drops (caused by missed oncreatemove calls)
    if (History::tickHist.size() > numElemToAvg)
    {
        double targetSum = 0;

        for (int i = History::tickHist.size() - 1; i > History::tickHist.size() - numElemToAvg; i--)
        {
            targetSum += vecPtr[i].*targetElemPtr;
        }

        targetSum /= numElemToAvg;

        // if targetSum is 130% of the nonsmoothed value, arbitrary
        if ((targetSum / value) * 100 > 130)
        {
            // arbitraryfcgnyhjdtrrtyhjdrtyhd
            smoothed *= 1.75;
        }
    }
    return smoothed;
}

void TickHistory::Update(CUserCmd* cmd)
{
    TickData curTick;

    const int DATA_HEIGHT = g_menu.strafetrainer.dataHeight;
    const int PREV_TICK = History::tickHist.size() - 1;

#pragma region CalculateCurTickFields
    double dbDeltaYaw = 0;

    curTick.vecViewangles = cmd->viewangles();
    curTick.vecPos = player->origin();
    curTick.vecVel = player->velocity();

    curTick.speed = std::hypot(curTick.vecVel.x, curTick.vecVel.y);

    // If tickHist has at least 2 ticks, we can calculate deltaYaw
    // and get old num jumps / strafes
    if (PREV_TICK >= 0)
    {
        dbDeltaYaw = SubtractAngle(curTick.vecViewangles.y, History::tickHist[PREV_TICK].vecViewangles.y);
        curTick.curJumps = History::tickHist[PREV_TICK].curJumps;
        curTick.curStrafes = History::tickHist[PREV_TICK].curStrafes;
    }

    // Mouse dir
    if (dbDeltaYaw > 0)         curTick.mouseDir = MouseDir::LEFT;
    else if (dbDeltaYaw < 0)    curTick.mouseDir = MouseDir::RIGHT;
    else                        curTick.mouseDir = MouseDir::NONE;

    // Key dir
    if (cmd->buttons() & in_moveleft && cmd->buttons() & in_moveright || cmd->buttons() & in_forward && cmd->buttons() & in_back)
    {
        curTick.keyDir = KeyDir::COUNTER_STRAFE;
    }
    else
    {
        if (cmd->buttons() & in_forward)
        {
            if (cmd->buttons() & in_moveleft)           curTick.keyDir = KeyDir::FORWARD_LEFT;
            else if (cmd->buttons() & in_moveright)     curTick.keyDir = KeyDir::FORWARD_RIGHT;
            else                                        curTick.keyDir = KeyDir::FORWARD;
        }
        else if (cmd->buttons() & in_back)
        {
            if (cmd->buttons() & in_moveleft)           curTick.keyDir = KeyDir::BACK_LEFT;
            else if (cmd->buttons() & in_moveright)     curTick.keyDir = KeyDir::BACK_RIGHT;
            else                                        curTick.keyDir = KeyDir::BACK;
        }
        else if (cmd->buttons() & in_moveleft)          curTick.keyDir = KeyDir::LEFT;
        else if (cmd->buttons() & in_moveright)         curTick.keyDir = KeyDir::RIGHT;
        else                                            curTick.keyDir = KeyDir::NONE;
    }

    if (fabs(MouseAndKeyPhiDiff(curTick.mouseDir, curTick.keyDir)) <= (M_PI / 2)
        && static_cast<int>(curTick.mouseDir) != 0 && static_cast<int>(curTick.keyDir) != 0)
    {
        curTick.strafeDir = curTick.mouseDir;
    }
    else if (PREV_TICK >= 0) curTick.strafeDir = History::tickHist[PREV_TICK].strafeDir;

    // Pos type
    if (player->is_in_air()) curTick.posType = PositionType::AIR;
    else curTick.posType = PositionType::GROUND;

    curTick.crouching = cmd->buttons() & in_duck;

    // Hacky way of getting the correct prespeed angle
    if (HasBeenOnGround(PREV_TICK))
    {
        curTick.perfDeltaYaw = 1.18;

        // Reset all statistics
        curTick.curJumps = 0;
        curTick.curStrafes = 0;
        // Call some function for extra stats?
    }
    else
    {
        // PerfAngle Calculation
        const int ACCEL_LIMIT = 30;
        float airAccel = Interfaces::convar->get_convar("sv_airaccelerate")->get_float(game_engine);
        double accelSpeed = min(Interfaces::globals->interval_per_tick() * 30 * airAccel, ACCEL_LIMIT);
        curTick.perfDeltaYaw = RAD2DEG(atan2f(accelSpeed, curTick.speed));
    }

    curTick.syncState = GetSyncState(cmd->buttons(), curTick.mouseDir);

    if (History::tickHist.size() >= 2)
    {
        // Smoothed/unsmoothed deltaYaw
        if (g_menu.strafetrainer.smooth)
        {
            curTick.deltaYaw = SmoothValueComparedToVector(fabs(dbDeltaYaw), History::tickHist.data(), &TickData::deltaYaw, 4);
        }
        else curTick.deltaYaw = fabs(dbDeltaYaw);

        // Lost speed
        curTick.lostSpeed = HasLostSpeed(g_menu.strafetrainer.speedLossTolerance, curTick.speed);

        // If jumped
        if (HasJumped()) curTick.curJumps++;

        // If strafed
        if (HasStrafed(curTick.mouseDir, curTick.keyDir, History::tickHist[PREV_TICK].strafeDir))
        {
            curTick.curStrafes++;
            curTick.latencyAmount = GetSyncLatency(curTick.strafeDir);
        }
        else curTick.latencyAmount = NOLATENCY;
    }
    else
    {
        curTick.deltaYaw = 0;
        curTick.latencyAmount = NOLATENCY;
    }

    // Misc
    curTick.scrolling = cmd->buttons() & in_jump;

#pragma endregion

    // Push curtick onto our tick history vector
    History::tickHist.push_back(curTick);


    if (History::tickHist.size() > 1)
    {
        // Removes unnecessary Data at the back of the stack
        while (History::tickHist.size() > g_menu.strafetrainer.historySize)
        {
            pop_front(History::tickHist);
        }
    }
}