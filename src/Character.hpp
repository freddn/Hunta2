#ifndef CHARACTER_H
#define CHARACTER_H

/*
 * Character class. Draw the player on the screen.
 * Character is a component. Need a position and physics
 * component aswell to function.
 */

#include "Texture.hpp"
#include "EntitySystem.hpp"

using namespace EntitySystem;

struct Character: Component
{
    public:
        Character();
        /* Load player. Loads a texture with the
         * character image and set position. */
        void init() override;
        /* Draw the player.*/
        void draw() override;

        void update() override;
        /* Takes in a key and move the char accordingly. */
        void moveChar(const Uint8 *key);
        /* Change the velocity of the player. */
        void setVelocity(int vel);
        /* Check if player is colliding with something. */
        bool checkCollision(int DIR);
        /* Load saved data. */
        void loadSaveFile(std::string char_name);
        virtual ~Character();
    protected:
    private:

    /* The directions.  */
    Texture *texture{nullptr};
    Position *position{nullptr};
    enum
    {
        NORTH = 1,
        EAST = 2,
        SOUTH = 3,
        WEST = 4
    };
    int vel = 4; // Velocity of the player. Default: 4.
    int coins; // Money
    int xPos; // x-position of the player.
    int yPos; // y-position of the player.
    int sticks; // ??
};

#endif // RENDERER_H





