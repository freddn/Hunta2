#ifndef TILE_H
#define TILE_H

#include "EntitySystem.hpp"
#include "Texture.hpp"

/* Tile class. Images used in background environments. */
struct Tile : Texture
{
    public:
        Tile();
        virtual ~Tile();
    protected:
    private:
    bool solid;
};

#endif // TILE_H








