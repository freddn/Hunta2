#ifndef COMPONENT_H
#define COMPONENT_H


struct Component
{
    Entity* entity{nullptr};
    virtual void update(float m);
    virtual void draw();

    virtual ~Component();
};

#endif // COMPONENT_H
