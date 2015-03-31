#ifndef ENTITYCREATOR_H
#define ENTITYCREATOR_H

#include "EntitySystem.hpp"

/* In this class you can create entitys that will be added to the
 * given manager.
 */
class EntityCreator
{
    public:
        EntityCreator();

        void createPlayer(EntitySystem::EntityManager manager,
                            const char* name);
        void createItem(EntitySystem::EntityManager,int itemNumber,
                            int x,int y, bool onGround);
        void createEnemy(EntitySystem::EntityManager,int enemyNumber,
                            int x,int y);


        virtual ~EntityCreator();
    protected:
    private:
};

#endif // ENTITYCREATOR_H
