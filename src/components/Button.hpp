
#ifndef HUNTA2_BUTTON_HPP
#define HUNTA2_BUTTON_HPP

#include "Texture.hpp"
#include <functional>

class Button {
public:
    void draw();
    void update(SDL_Event *event, int mouseX, int mouseY);

    /**
     * When the button is clicked this function will be executed.
     */
    void onClick(std::function<void()> func);
    void setImg(std::string img, bool clipped, int cw, int ch);
    void setRect(int x, int y, int w, int h);
    bool mouseOverButton(int mouseX, int mouseY);
    Texture* getButtonTextField();
private:
    Texture buttonText;
    Texture buttonBackground;

    int buttonX;
    int buttonY;
    int buttonW;
    int buttonH;
    std::function<void ()> function = nullptr;

    bool pressed = false;
    bool hoover = false;

};


#endif //HUNTA2_BUTTON_HPP
