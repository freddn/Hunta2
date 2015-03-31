#ifndef TILE_H
#define TILE_H

#include "Texture.hpp"

/* Tile class. Images used in background environments. */
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








