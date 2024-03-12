//
// Created by fredrik on 3/1/16.
//

#ifndef HUNTA2_LUAGAMEFUNCTIONS_HPP
#define HUNTA2_LUAGAMEFUNCTIONS_HPP


#include "../Game.hpp"
#include "../common/HelperFunctions.hpp"

namespace lua_functions {


    int playerAddHp(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 1) {
            game::getPlayerController()->increaseHp(lua_tonumber(l_state,1));
        }
        return 0;
    }

    int getPlayerX(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 0) {
            lua_pushinteger(l_state, game::getPlayerController()->getPosX());
            return 1;
        }
        return 0;
    }

    int getPlayerY(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 0) {
            lua_pushinteger(l_state, game::getPlayerController()->getPosY());
            return 1;
        }

        return 0;
    }

}

#endif //HUNTA2_LUAGAMEFUNCTIONS_HPP
