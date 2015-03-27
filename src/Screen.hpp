#ifndef SCREEN_H
#define SCREEN_H

#include <sstream>

#include "Texture.hpp"
//#include "Game.hpp"
//#include "EntitySystem.hpp"

struct Screen// : EntitySystem::Component
{
    public:
        virtual void init();// override;
        virtual void update();// override;
        virtual void draw();// override;
        void renderStart();
        void renderEnd();
        int getSelected();
        virtual ~Screen();// override;
    protected:
    private:
        const Uint8 *key = NULL;
        std::stringstream tempText;
        int x = 0;
        int y = 0;
        int selected = 0;
        Texture timerText;
        Texture fpsText;
};

#endif // SCREEN_H
