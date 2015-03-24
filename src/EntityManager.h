#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory>
#include <algorithm>
#include "Entity.hpp"


struct EntityManager
{
    public:
        //EntityManager();
        void update(float m);
        void draw();
        Entity& addEntity();

        virtual ~EntityManager();
    protected:
    private:
    std::vector<std::unique_ptr<Entity>> entities;
};

#endif // ENTITYMANAGER_H
