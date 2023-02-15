#pragma once
#include "../Indices/Indices.h"

class ConVar {
public:
    float get_float(int game_engine)
    {
        if (game_engine == 1)
        {
            using original_fn = float(__thiscall*)(void*);
            return (*(original_fn**)this)[12](this);
        }
        if (game_engine == 2)
        {
            return *reinterpret_cast<float*>(uintptr_t(this) + 0x2C);
        }
        return 0;
    }
};

class IConVar {
public:
    ConVar* get_convar(const char* var_name)
    {
        using original_fn = ConVar * (__thiscall*)(IConVar*, const char*);
        return (*reinterpret_cast<original_fn**>(this))[Indices::get_convar](this, var_name);
    }
};