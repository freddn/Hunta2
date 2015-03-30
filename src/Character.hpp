#ifndef CHARACTER_H
#define CHARACTER_H
#include "Texture.hpp"
#include "EntitySystem.hpp"

using namespace EntitySystem;

struct Character: public Texture, Component
{
    public:
        Character();
        void init() override;
        void draw() override;
        void update() override;
        void moveChar(const Uint8 *key);

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
    int vel = 4;
    int coins;
    int xPos;
    int yPos;
    int sticks;
};

#endif // RENDERER_H





