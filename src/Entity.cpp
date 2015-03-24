#include "Entity.hpp"

Entity::Entity()
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}


void Entity::draw()
{
    for(auto& c : components) c->draw();
}

void Entity::update(float m)
{
    for(auto& c : components) c->update(m);
}

template<typename T, typename... TArgs>
T& Entity::addComponent(TArgs&&... mArgs)
{
    T* c(new T(std::forward<TArgs>(mArgs)...));

    c->entity = this;

    std::unique_ptr<Component> uPtr{c};

    components.emplace_back(std::move(uPtr));

    return *c;
}
