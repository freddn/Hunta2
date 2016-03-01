//
// Created by fredrik on 3/1/16.
//

#ifndef HUNTA2_ENUMS_HPP
#define HUNTA2_ENUMS_HPP

namespace game {

    /** The different states of the game. */
    enum State {    MAINMENU,
        CHARCREATION,
        INGAME,
        PAUSED,
        GAMEOVER,
        EDITOR };

    /** Some directions the character can have. */
    enum Direction {    NORTH,
        SOUTH,
        WEST,
        EAST };

    /** Different tiles used by the Editor. */
    enum Selected { GRASS,
        GROUND,
        WATER };

    /** Different entity types. */
    enum EntityGroup : std::size_t {    PLAYER,
        ITEM,
        ENEMY,
        ENVIRONMENT,
        PROJECTILE,
        TILE,
        X };
}

#endif //HUNTA2_ENUMS_HPP
