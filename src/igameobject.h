#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H


class IGameObject
{
public:
    IGameObject();

    virtual void update() = 0;
    virtual void draw() = 0;
};

#endif // IGAMEOBJECT_H
