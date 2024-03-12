//
// Created by fredrik on 3/2/16.
//

#ifndef HUNTA2_TEXTBOX_HPP
#define HUNTA2_TEXTBOX_HPP

#include <string>
#include "../components/Texture.hpp"

class TextBox {
public:
    TextBox(int x, int y, int w, int h, const std::string &str);
    TextBox(const std::string &str);

    void init(SDL_Renderer *renderer, SDL_Color *color, TTF_Font *font);
    void draw();
    void setText(const std::string &str);
    void setActive(bool active);
    bool isActive();
    void remove();

    virtual ~TextBox();

private:
    std::vector<std::unique_ptr<Texture>> text;

    SDL_Texture *background{nullptr};
    SDL_Texture *backgroundOutline{nullptr};
    SDL_Rect boxRect;
    SDL_Rect backgroundOutlineRect;

    SDL_Renderer *renderer{nullptr};
    bool active = true;

    int xPos;
    int yPos;
    int width;
    int height;
    std::string str;
};


#endif //HUNTA2_TEXTBOX_HPP
