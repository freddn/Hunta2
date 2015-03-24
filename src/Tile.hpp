#ifndef TILE_H
#define TILE_H
#include "Texture.hpp"

class Tile: public Texture
{
    public:
        Tile();
        virtual ~Tile();
    protected:
    private:
    bool solid;
};

#endif // TILE_H








