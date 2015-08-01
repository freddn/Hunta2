#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "EntitySystem.hpp"
#include "Position.hpp"
#include "Texture.hpp"
#include <SDL2/SDL.h>
#include <sstream>
#include <SDL2/SDL_ttf.h>
#include "LTimer.hpp"

using namespace EntitySystem;

/**
 * Represents the HP-bar of living things. This is a component that can be added
 * to an entity. The hpbar contains some textures created from rectangles and
 * the green rectangle will shrink in size accordingly to current hp/max hp.
 *
 * This class represents the entitys health and is responsible for destroying the
 * entity when the hp is 0, it is not supposed to be like this and more components
 * will be added, or if the Character/Enemy component will be responsible. (TODO)
 */
struct Health : Component {
public:
    Health(int hp);

    void init();
    void draw();
    void update();

    void setHp(int health);
    void damage(int atk, int seed);
    void setMaxHp(int maxhealth);
    void setDisplay(bool display);
    int getHp();
    void displayDamage(int damage);
    virtual ~Health();
protected:
private:
    Position *position{nullptr};

    SDL_Rect hpBarBGRect{0,0,32,5};
    SDL_Rect hpBarRect{0,0,32,5};
    SDL_Rect hpBarOutlineRect{0,0,34,7};
    SDL_Texture *hpBarBG;
    SDL_Texture *hpBar;
    SDL_Texture *hpBarOutline;

    std::stringstream dmgText;
    Texture dmgDisplay;
    Texture dmgBg;
    Texture healBg;
    Texture defBg;
    int dmgDone = 0;
    bool displayDmgDone = false;
    bool alive = true;
    int health = 0;
    int maxHP = 0;
    bool isDisplayed = false;
    LTimer hpTimer;
};

#endif // HEALTHBAR_H
