#pragma once
#include "../Indices/Indices.h"
#include "../Interfaces/Interfaces.h"
#include "../hooks/hooks.h"

class player_t;
inline int game_engine = -1;
#define ENGINE_CSGO 1
#define ENGINE_CSS 2

inline bool menu_open = false;
inline player_t* player;
inline std::string game;