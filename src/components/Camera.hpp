#ifndef CAMERA_H
#define CAMERA_H

#include "../EntitySystem.hpp"
#include "Position.hpp"


struct Camera : EntitySystem::Component {
public:
    Camera();

    void init();
    void update();

    void setX(int x);
    void setY(int y);
    int getX();
    int getY();

    void setW(int w);
    void setH(int h);
    int getW();
    int getH();

    virtual ~Camera();
protected:
private:
    Position *position{nullptr};
    int posX = 0;
    int posY = 0;
    int screenWidth = 640;
    int screenHeight = 480;
};

#endif // CAMERA_H
