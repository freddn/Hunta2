//
// Created by fredrik on 3/1/16.
//

#ifndef HUNTA2_LUAGENERALFUNCTIONS_HPP
#define HUNTA2_LUAGENERALFUNCTIONS_HPP

#include "Game.hpp"
#include "HelperFunctions.hpp"

namespace lua_functions {

    int playerSavegame(lua_State *lua_state) {
        int argc = lua_gettop(lua_state);
        if (argc == 3) {
            int slot = lua_tonumber(lua_state, 1);
            std::string playerName = lua_tostring(lua_state, 2);
            int level = lua_tonumber(lua_state, 3);
            game::getSaveSlotSelection()->setSlot(slot, playerName, level);
            game::getCharacterCreationScreen()->saveSlot(slot, playerName, level);
        }
        return 0;
    }


    int yield(lua_State *l_state) {
        lua_yield(l_state, 0);
        return 0;
    }
}

#endif //HUNTA2_LUAGENERALFUNCTIONS_HPP
