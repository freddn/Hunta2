
#ifndef HUNTA2_BUTTON_HPP
#define HUNTA2_BUTTON_HPP


#include <SDL2/SDL_rect.h>
#include "../components/Texture.hpp"

class Button {
public:
    void draw();
    void update(SDL_Event *event, int mouseX, int mouseY);

    /**
     * When the button is clicked this function will be executed.
     */
    void onClick(std::function<void()> func);

    void setButtonText(std::string text, SDL_Color *color, TTF_Font *font);
    void setImg(std::string img, bool clipped, int cw, int ch);
    void setRect(int x, int y, int w, int h);
    bool mouseOverRect(SDL_Rect r, int mouseX, int mouseY);
private:
    Texture buttonText;
    Texture buttonBackground;

    SDL_Rect buttonRect;
    std::function<void ()> function = nullptr;

    bool pressed = false;
    bool hoover = false;

};


#endif //HUNTA2_BUTTON_HPP
