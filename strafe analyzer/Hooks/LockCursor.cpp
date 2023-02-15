#include "hooks.h"

void __stdcall Hooks::LockCursor::Hook()
{
    if (game_engine == ENGINE_CSGO)
    {
        if (menu_open)
        {
            Interfaces::surface->unlock_cursor();
            //Interfaces::input->enable_input(false);
            return;
        }
        else Interfaces::input->enable_input(true);
    }

    LockCursor_original(Interfaces::surface);
}