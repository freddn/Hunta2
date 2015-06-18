#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "EntitySystem.hpp"
#include "Position.hpp"
#include <SDL2/SDL.h>


using namespace EntitySystem;

struct HealthBar : Component {
public:
    HealthBar(int hp);

    void init();
    void draw();
    void update();

    void setHp(int health);
    void setMaxHp(int maxhealth);
    void setDisplay(bool display);
    int getHp();
    virtual ~HealthBar();
protected:
private:
    Position *position{nullptr};

    SDL_Rect hpBarBGRect{0,0,32,5};
    SDL_Rect hpBarRect{0,0,32,5};
    SDL_Rect hpBarOutlineRect{0,0,34,7};
    SDL_Texture *hpBarBG;
    SDL_Texture *hpBar;
    SDL_Texture *hpBarOutline;
    int health = 0;
    int maxHP = 0;
    bool isDisplayed = true;
};

#endif // HEALTHBAR_H
