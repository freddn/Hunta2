#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H

#include "EntitySystem.hpp"
#include "Position.hpp"
struct MouseController  : EntitySystem::Component {
public:
    MouseController();
    MouseController(bool x, bool y);

    void init();
    void update();

    void setMouseX(int x);
    void setMouseY(int y);

    int getMouseX();
    int getMouseY();

    bool rightMouseButton();
    bool leftMouseButton();

    void setRMouseBtn(bool rMouse);
    void setLMouseBtn(bool lMouse);
    void setCenteredX(bool c);
    void setCenteredY(bool c);

    /// Set function to run when cliked.

    virtual ~MouseController();
protected:
private:
    Position *position = nullptr;
    bool rMouseBtn = false;
    bool lMouseBtn = false;
    bool controllX = true;
    bool controllY = true;

    int width = 32;
    int height = 32;

    int mouseX = 0;
    int mouseY = 0;
};

#endif // MOUSECONTROLLER_H
