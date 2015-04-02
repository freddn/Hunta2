#ifndef ENTITYCREATOR_H
#define ENTITYCREATOR_H

#include <vector>
#include <memory>

#include "EntitySystem.hpp"

using namespace EntitySystem;
/* In this class you can create entitys that will be added to the
 * given manager.
 */
class EntityCreator
{
    public:
        EntityCreator();

        Entity& createPlayer(EntitySystem::EntityManager *mManager);
        Entity& createItem(EntitySystem::EntityManager *mManager,int itemNumber,
                            int x,int y, bool onGround);
        Entity& createEnemy(EntitySystem::EntityManager *mManager,int enemyNumber,
                            int x,int y);


        virtual ~EntityCreator();
    protected:
    private:
};

#endif // ENTITYCREATOR_H
