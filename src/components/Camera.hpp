#ifndef CAMERA_H
#define CAMERA_H

#include "../EntitySystem.hpp"
#include "Position.hpp"


struct Camera : EntitySystem::Component {
public:
    Camera();

    void init();
    void update();

    virtual ~Camera();
protected:
private:
    Position *position{nullptr};
    int posX = 0;
    int posY = 0;
};

#endif // CAMERA_H
