
#include "Camera.hpp"

#include "Game.hpp"

Camera::Camera() {
    //ctor
}

Camera::~Camera() {
    //dtor
}

void Camera::init() {
    if(entity->hasComponent<Position>()) {
        position = &entity->getComponent<Position>();
    }


}

void Camera::update() {
    //std::cout << "characters " << std::endl;
    /// TODO implement camera and keyboardcontroller for the player...
    if(position != nullptr) {

        if( (position->getX() - (game::getWidth()/2)  > 0 ||
            game::getTextureMapController()->getMap(game::getTextureMapController()->getCurrentMap())->getMapAt(game::WEST) > 0 ) &&
            ((position->getX() + (game::getWidth()/2)) < game::getBackground()->w ||
            game::getTextureMapController()->getMap(game::getTextureMapController()->getCurrentMap())->getMapAt(game::EAST) > 0) ) {
            game::getOffset()->x = position->getX() - game::getWidth()/2;
        }
        if(((position->getY() - (game::getHeight()/2)) > 0 ||
            game::getTextureMapController()->getMap(game::getTextureMapController()->getCurrentMap())->getMapAt(game::NORTH) > 0) &&
            ((position->getY() + (game::getHeight()/2)) < game::getBackground()->h ||
            game::getTextureMapController()->getMap(game::getTextureMapController()->getCurrentMap())->getMapAt(game::SOUTH) > 0)) {
            game::getOffset()->y = position->getY() - game::getHeight()/2;
        }
    }

}

