#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <memory>
#include "Component.hpp"

class Entity
{
    public:
        Entity();

        void update(float m);
        void draw();

        bool isAlive() const {return alive;};
        void destroy() {alive = false;};

        template<typename T, typename... TArgs>
        T& addComponent(TArgs&&... mArgs);

        virtual ~Entity();
    private:
        bool alive{true};
        std::vector<std::unique_ptr<Component>> components;
};

#endif // ENTITY_H
