#include "Camera.hpp"

#include "../Global.hpp"
#include "../Enums.hpp"

Camera::Camera() { }

Camera::~Camera() { }

void Camera::init() {
    if(entity->hasComponent<Position>()) {
        position = &entity->getComponent<Position>();
    }
}

void Camera::update() {
    if(position != nullptr) {
        if( (position->getX() - (game::getOffset()->w/2)  > 0 ||
            game::getTextureMapController()->getMap(game::getTextureMapController()->getCurrentMap())->getMapAt(game::WEST) > 0 ) &&
            ((position->getX() + (game::getOffset()->w/2)) < game::getBackground()->w ||
            game::getTextureMapController()->getMap(game::getTextureMapController()->getCurrentMap())->getMapAt(game::EAST) > 0) ) {
            game::getOffset()->x = (int)position->getX() - game::getOffset()->w/2;
        }
        if(((position->getY() - (game::getOffset()->h/2)) > 0 ||
            game::getTextureMapController()->getMap(game::getTextureMapController()->getCurrentMap())->getMapAt(game::NORTH) > 0) &&
            ((position->getY() + (game::getOffset()->h/2)) < game::getBackground()->h ||
            game::getTextureMapController()->getMap(game::getTextureMapController()->getCurrentMap())->getMapAt(game::SOUTH) > 0)) {
            game::getOffset()->y = (int)position->getY() - game::getOffset()->h/2;
        }
    }

}

