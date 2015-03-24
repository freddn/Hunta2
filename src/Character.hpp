#ifndef CHARACTER_H
#define CHARACTER_H
#include "Texture.hpp"

class Character: public Texture
{
    public:
        Character();

        void moveChar(int vel, const Uint8 *key);

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
    int width = 640;
    int height = 480;
    int coins;
    int xPos;
    int yPos;
    int sticks;
};

#endif // RENDERER_H





