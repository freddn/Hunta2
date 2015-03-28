#ifndef CHARACTER_H
#define CHARACTER_H
#include "Texture.hpp"
#include "EntitySystem.hpp"

class Character: public Texture, EntitySystem::Component
{
    public:
        Character();
        void init();
        void draw();
        void update();
        void moveChar(int vel, const Uint8 *key);

        void setVelocity(int vel);

        bool checkCollision(int DIR);

        void loadSaveFile(std::string char_name);
        virtual ~Character();
    protected:
    private:

    /* STATS AND STUFF */
    enum
    {
        NORTH = 1,
        EAST = 2,
        SOUTH = 3,
        WEST = 4
    };
    int coins;
    int xPos;
    int yPos;
    int sticks;
};

#endif // RENDERER_H





