//
// Created by fredrik on 3/1/16.
//

#ifndef HUNTA2_LUAFUNCTIONS_HPP
#define HUNTA2_LUAFUNCTIONS_HPP

#include "Global.hpp"
#include "Enums.hpp"

namespace lua_functions {

    int loadTile(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 5) {
            int mapID = lua_tonumber(l_state,1); // mapid
            int id = lua_tonumber(l_state,2); // id
            int index = lua_tonumber(l_state,3); // index
            int x = lua_tonumber(l_state,4); // x
            int y = lua_tonumber(l_state,5); // y
            game::getTextureMapController()->loadTile(mapID,id,index,x,y);
        }
        return 0;
    }

    int loadEnemy(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 5) {
            int mapID = lua_tonumber(l_state,1); // mapid
            int id = lua_tonumber(l_state,2); // id
            int index = lua_tonumber(l_state,3); // index
            int x = lua_tonumber(l_state,4); // x
            int y = lua_tonumber(l_state,5); // y
            game::getTextureMapController()->loadEnemy(mapID,id,index,x,y);
        }
        return 0;
    }

    int loadEnvironment(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 5) {
            int mapID = lua_tonumber(l_state,1); // mapid
            int id = lua_tonumber(l_state,2); // id
            int index = lua_tonumber(l_state,3); // index
            int x = lua_tonumber(l_state,4); // x
            int y = lua_tonumber(l_state,5); // y
            game::getTextureMapController()->loadEnvironment(mapID,id,index,x,y);
        }
        return 0;
    }

    int loadItem(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc > 2) {
            int id =  lua_tonumber(l_state,1);
            int amount = lua_tonumber(l_state,2);
            int onGround = lua_tonumber(l_state,3);
            if(argc > 4) {
                int x = lua_tonumber(l_state,4);
                int y = lua_tonumber(l_state,5);
                if(onGround == 0)
                    game::getInventory()->addItem(id, amount, x, y);
            } else {
                if(onGround == 0)
                    game::getInventory()->addItem(id, amount);
            }
        }
        return 0;
    }

    int loadCharacter(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 9) {
            game::getPlayerController()->setName(lua_tostring(l_state,1));
            game::getPlayerController()->setLevel(lua_tonumber(l_state,2));
            game::getPlayerController()->setExperience(lua_tonumber(l_state,3));
            game::getPlayerController()->setHp(lua_tonumber(l_state,4));
            game::getPlayerController()->setCurrentHp(lua_tonumber(l_state,5));
            game::getPlayerController()->setAtk(lua_tonumber(l_state,6));
            game::getPlayerController()->setDef(lua_tonumber(l_state,7));
            game::getPlayerController()->setPosX(lua_tonumber(l_state,8));
            game::getPlayerController()->setPosY(lua_tonumber(l_state,9));
        }
        return 0;
    }

    /// ASSET LOADING
    int loadTileData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 3) {
            int id = lua_tonumber(l_state,1); // id
            std::string img = lua_tostring(l_state,2); // image
            int solid = lua_tonumber(l_state,3); // solid
            game::getTextureManager()->loadTexture(img);
            game::getTextureMapController()->loadTileData(id,img,solid == 1);
            game::getEditor()->loadIcon(img,id,game::TILE);
        }
        return 0;
    }

    int loadEnvironmentData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 3) {
            int id = lua_tonumber(l_state,1); // id
            std::string img = lua_tostring(l_state,2); // image
            int solid = lua_tonumber(l_state,3); // solid
            game::getTextureManager()->loadTexture(img);
            game::getTextureMapController()->loadEnvironmentData(id,img,solid == 1);
            game::getEditor()->loadIcon(img,id,game::ENVIRONMENT);
        }
        return 0;
    }

    int loadArmorData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 9) {
            int id = lua_tonumber(l_state,1); // id
            std::string name = lua_tostring(l_state,2); // name
            int level = lua_tonumber(l_state,3); // id
            std::string img = lua_tostring(l_state,4); // image
            std::string desc = lua_tostring(l_state,5); // desc
            int price = lua_tonumber(l_state,6); // price
            int atk = lua_tonumber(l_state,7); // atk
            int def = lua_tonumber(l_state,8); // def
            int hp = lua_tonumber(l_state,9); // hp
            game::getTextureManager()->loadTexture(img);
            game::getItemManager()->loadArmor(id,name,level,img,desc,price,atk,def,hp);
        }
        return 0;
    }

    int loadUsablesData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 9) {
            int id = lua_tonumber(l_state,1); // id
            std::string name = lua_tostring(l_state,2); // name
            int level = lua_tonumber(l_state,3);
            int maxStack = lua_tonumber(l_state,4);
            std::string img = lua_tostring(l_state,5); // image
            std::string desc = lua_tostring(l_state,6); // desc
            int price = lua_tonumber(l_state,7); // price
            int heal = lua_tonumber(l_state,8); // atk
            std::string script = lua_tostring(l_state,9);
            game::getTextureManager()->loadTexture(img);
            game::getItemManager()->loadUsable(id,name,level,maxStack,img,desc,price,heal,script);
        }
        return 0;
    }

    int loadWeaponsData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 9) {
            int id = lua_tonumber(l_state,1); // id
            std::string name = lua_tostring(l_state,2); // name
            int level = lua_tonumber(l_state,3); // id
            std::string img = lua_tostring(l_state,4); // image
            std::string desc = lua_tostring(l_state,5); // desc
            int price = lua_tonumber(l_state,6); // price
            int atk = lua_tonumber(l_state,7); // atk
            int def = lua_tonumber(l_state,8); // def
            int hp = lua_tonumber(l_state,9); // hp
            game::getTextureManager()->loadTexture(img);
            game::getItemManager()->loadWeapon(id,name,level,img,desc,price,atk,def,hp);
        }
        return 0;
    }

    int loadMapData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 7) {
            int id = lua_tonumber(l_state,1); // id
            int x = lua_tonumber(l_state,2); // x pos
            int y = lua_tonumber(l_state,3); // y pos
            int north = lua_tonumber(l_state,4); // north
            int east = lua_tonumber(l_state,5); // east
            int south = lua_tonumber(l_state,6); // south
            int west = lua_tonumber(l_state,7); // west
            game::getTextureMapController()->loadMapData(id,x,y,north,east,south,west);
        }
        return 0;
    }

    int loadEnemiesData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 9) {
            int id = lua_tointeger(l_state,1); // id
            std::string name = lua_tostring(l_state,2); // name
            std::string img = lua_tostring(l_state,3); // image
            int hp = lua_tointeger(l_state,4); // hp
            int level = lua_tointeger(l_state,5); // level
            int atk = lua_tointeger(l_state,6); // atk
            int exp = lua_tointeger(l_state,7); // exp
            int width = lua_tointeger(l_state,8); // width
            int height = lua_tointeger(l_state,9); // height
            game::getEnemyDataController()->loadEnemy(id, name, img, hp, level, atk,exp, width, height);

            game::getTextureManager()->loadTexture(img);
            game::getTextureMapController()->loadEnemyData(id,img);
            game::getEditor()->loadIcon(img,id,game::ENEMY);
        }
        return 0;
    }

    int loadMiscItemData(lua_State *l_state) {
        int argc = lua_gettop(l_state);
        if(argc == 6) {
            int id = lua_tonumber(l_state,1); // id
            std::string name = lua_tostring(l_state,2); // name
            int maxStack = lua_tonumber(l_state,3); // stack
            std::string img = lua_tostring(l_state,4); // image
            std::string desc = lua_tostring(l_state,5); // desc
            int price = lua_tonumber(l_state,6); // price
            game::getTextureManager()->loadTexture(img);
            game::getItemManager()->loadMisc(id,name,maxStack,img,desc,price);
        }
        return 0;
    }
}


#endif //HUNTA2_LUAFUNCTIONS_HPP
