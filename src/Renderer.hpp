#ifndef RENDERER_H
#define RENDERER_H

#include <map>
#include "Tile.hpp"

class Renderer
{
    public:
        Renderer();

        void setMap(std::map<int,Tile> tile_map);
        void render(SDL_Renderer *renderer);
        void setRenderer(SDL_Renderer *renderer);
        void addTexture(Texture *texture);

        virtual ~Renderer();
    protected:
    private:
};

#endif // RENDERER_H






