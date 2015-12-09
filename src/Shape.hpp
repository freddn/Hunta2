#ifndef SHAPE_H
#define SHAPE_H

#include "EntitySystem.hpp"
#include "Position.hpp"
#include "SDL2/SDL.h"

using namespace EntitySystem;

struct Shape : Component {
public:
    Shape();
    Shape(int w, int h,int r,int g,int b);
    void init();
    void draw();

    int getWidth();
    int getHeight();

    virtual ~Shape();
protected:
private:
    Position *position{nullptr};
    int width = 32;
    int height = 32;
    int red = 0;
    int green = 0;
    int blue = 0;
    SDL_Texture *shape{nullptr};
};

#endif // SHAPE_H
