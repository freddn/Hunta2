#include "Tile.hpp"

Tile::Tile(int id) {
    tileID = id;
}

Tile::~Tile() {
    //dtor
}

int Tile::getID() {
    return tileID;
}
