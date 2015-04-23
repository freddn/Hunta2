#ifndef CHARACTER_H
#define CHARACTER_H

#include "Texture.hpp"
#include "GPhysics.hpp"
#include "EntitySystem.hpp"

using namespace EntitySystem;

/*
 * Character class. Draw the player on the screen.
 * Character is a component. Need a position and physics
 * component aswell to function.
 */
struct Character: Component
{
    public:
        Character();
        Character(EntityManager *m);
        /* Load player. Loads a texture with the
         * character image and set position. */
        void init() override;
        /* Draw the player.*/
        void draw() override;

        void update() override;
        /* Takes in a key and move the char accordingly. */
        void moveChar(const Uint8 *key);
        /* Check if player is colliding with something. */
        bool checkCollision(int DIR);
        /* Load saved data. */
        void loadSaveFile(std::string char_name);
        virtual ~Character();
    protected:
    private:

        GPhysics *physics{nullptr};
        Texture *texture{nullptr};
        Position *position{nullptr};

        EntityManager *manager{nullptr};

        int xPos; // x-position of the player.
        int yPos; // y-position of the player.
};

#endif // RENDERER_H





