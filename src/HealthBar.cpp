#include "HealthBar.hpp"

#include "Game.hpp"

HealthBar::HealthBar(int hp) {
    maxHP = hp;
    health = hp;
    //ctor
}

HealthBar::~HealthBar() {
    SDL_DestroyTexture(hpBarBG);
    SDL_DestroyTexture(hpBar);
    SDL_DestroyTexture(hpBarOutline);
}

void HealthBar::init() {
    position = &entity->getComponent<Position>();

    SDL_Surface *temp = SDL_CreateRGBSurface(0,hpBarBGRect.w,hpBarBGRect.h,32,0,0,0,0);
    SDL_FillRect(temp,NULL,SDL_MapRGB(temp->format,255,0,0));
    hpBarBG = SDL_CreateTextureFromSurface(game::getRenderer(),temp);

    SDL_FreeSurface(temp);

    temp = SDL_CreateRGBSurface(0,hpBarRect.w,hpBarRect.h,32,0,0,0,0);
    SDL_FillRect(temp,NULL,SDL_MapRGB(temp->format,0,255,0));
    hpBar = SDL_CreateTextureFromSurface(game::getRenderer(),temp);

    SDL_FreeSurface(temp);

    temp = SDL_CreateRGBSurface(0,hpBarOutlineRect.w,hpBarOutlineRect.h,32,0,0,0,0);
    SDL_FillRect(temp,NULL,SDL_MapRGB(temp->format,0,0,0));
    hpBarOutline = SDL_CreateTextureFromSurface(game::getRenderer(),temp);

    SDL_FreeSurface(temp);

    hpBarRect.y = position->getY()-10;
    hpBarRect.x = position->getX();

    hpBarBGRect.y = position->getY()-10;
    hpBarBGRect.x = position->getX();

    hpBarOutlineRect.y = position->getY() - 11;
    hpBarOutlineRect.x = position->getX()- 1;

}

void HealthBar::draw() {
    if(isDisplayed) {
        hpBarBGRect.x = position->getX() - game::getOffset()->x;
        hpBarRect.x = position->getX() - game::getOffset()->x;
        hpBarOutlineRect.x = position->getX() - game::getOffset()->x - 1;

        hpBarBGRect.y = position->getY() - 10 - game::getOffset()->y;
        hpBarRect.y = position->getY()- 10 - game::getOffset()->y;
        hpBarOutlineRect.y = position->getY() - 11 - game::getOffset()->y;

        SDL_RenderCopy(game::getRenderer(),hpBarOutline,NULL,&hpBarOutlineRect);

        SDL_RenderCopy(game::getRenderer(),hpBarBG,NULL,&hpBarBGRect);

        SDL_RenderCopy(game::getRenderer(),hpBar,NULL,&hpBarRect);
    }



}

void HealthBar::update() {

}

void HealthBar::setHp(int hp) {
    health = hp;
    hpBarRect.w = 32 * ((float)health/(float)maxHP);
    if(hpBarRect.w < 1) {
        entity->destroy();
    }
}

void HealthBar::setMaxHp(int maxhealth) {
    maxHP = maxhealth;
}

void HealthBar::setDisplay(bool display) {

}

int HealthBar::getHp() {
    return health;
}

