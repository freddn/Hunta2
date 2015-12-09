#ifndef ICON_H
#define ICON_H

#include "SDL2/SDL_image.h"
#include "Texture.hpp"

class Icon {
public:
    Icon(std::string img);
    Icon(std::string img, int width, int height);
    void init();
    void draw();

    bool isSelected();
    void setSelected(bool);

    std::size_t getType();
    void setType(std::size_t t);

    int getID();
    void setID(int id);

    std::string getImagePath();

    void setX(int x);
    void setY(int y);

    virtual ~Icon();
protected:
private:
    bool selected = false;
    std::size_t type = -1;
    int iconID = -1;
    int posX = 0;
    int posY = 0;
    Texture iconImage;
    SDL_Texture *rSelect = nullptr;

};

#endif // ICON_H
