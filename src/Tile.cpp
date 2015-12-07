#include "Tile.hpp"

Tile::Tile(int id) {
    tileID = id;
}

Tile::~Tile() { }

int Tile::getID() {
    return tileID;
}
