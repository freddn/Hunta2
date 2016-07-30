#include "Health.hpp"

#include "../Global.hpp"
#include "../Enums.hpp"
#include "Enemy.hpp"

Health::Health(int hp) {
    maxHP = hp;
    health = hp;
    initHpBar();
}

Health::~Health() {
    hpBarBG = nullptr;
    hpBar = nullptr;
    hpBarOutline = nullptr;
}

void Health::initHpBar() {
    dmgBg.loadFromFile("data/bloodSplash2.png");
    healBg.loadFromFile("data/heal.png");
    defBg.loadFromFile("data/shield.png");

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
}

void Health::init() {
    position = &entity->getComponent<Position>();
    hpBarRect.y = (int)position->getY()-10;
    hpBarRect.x = (int)position->getX();

    hpBarBGRect.y = (int)position->getY()-10;
    hpBarBGRect.x = (int)position->getX();

    hpBarOutlineRect.y = (int)position->getY() - 11;
    hpBarOutlineRect.x = (int)position->getX()- 1;
}

void Health::draw() {
    if(isDisplayed) {
        hpBarBGRect.x = (int)position->getX() - game::getOffset()->x;
        hpBarRect.x = (int)position->getX() - game::getOffset()->x;
        hpBarOutlineRect.x = (int)position->getX() - game::getOffset()->x - 1;

        hpBarBGRect.y = (int)position->getY() - 10 - game::getOffset()->y;
        hpBarRect.y = (int)position->getY()- 10 - game::getOffset()->y;
        hpBarOutlineRect.y = (int)position->getY() - 11 - game::getOffset()->y;

        SDL_RenderCopy(game::getRenderer(),hpBarOutline,NULL,&hpBarOutlineRect);

        SDL_RenderCopy(game::getRenderer(),hpBarBG,NULL,&hpBarBGRect);

        SDL_RenderCopy(game::getRenderer(),hpBar,NULL,&hpBarRect);
    }

    if(displayDmgDone) {
        if(!hpTimer.isStarted()) {
            hpTimer.start();
        } else if(hpTimer.getTicks() > 600) {
            displayDmgDone = false;
            hpTimer.stop();
        }
        if(dmgDone < 0)
            dmgBg.render((int)position->getX() +9- game::getOffset()->x,(int)position->getY() -33 - game::getOffset()->y,nullptr);
        else if(dmgDone > 0)
            healBg.render((int)position->getX() +9- game::getOffset()->x,(int)position->getY() -33 - game::getOffset()->y,nullptr);
        else
            defBg.render((int)position->getX() +9- game::getOffset()->x,(int)position->getY() -33 - game::getOffset()->y,nullptr);
        dmgDisplay.render((int)position->getX() +14 - game::getOffset()->x,(int)position->getY() -30 - game::getOffset()->y,nullptr);
    }
}

void Health::update() {

}



void Health::setHp(int hp) {
    displayDamage(hp - health);
    health = hp;
    hpBarRect.w = 32 * (int)((float)health/(float)maxHP);
    if(health < 1) {
        alive = false;
        if(entity->hasComponent<Enemy>())
            entity->getComponent<Enemy>().onDeath();
        else
            game::setCurrentState(game::MAINMENU);
    }
}

int Health::damage(int atk, int seed) {
    int atkVal = 0;
    if(alive) {
        isDisplayed = true;
        srand((unsigned int)seed);
        atkVal = rand() % atk;
        setHp(health-atkVal);
    }
    return atkVal;
}

void Health::displayDamage(int damage) {
    dmgDone = damage;
    displayDmgDone = true;
    dmgText.str("");
    dmgText << std::abs(damage);
    SDL_Color dmgColor;
    if(damage < 0)
        dmgColor = {0,0,0,0}; /// (Red, Green, Blue, Alpha)
    else if(damage > 0)
        dmgColor = {0,0,0,0};
    else
        dmgColor = {255,255,255,0};

    dmgDisplay.loadFromText(dmgText.str(),&dmgColor,game::getDmgFont());
    hpTimer.start();
}

void Health::setMaxHp(int maxhealth) {
    maxHP = maxhealth;
}

int Health::getHp() {
    return health;
}

