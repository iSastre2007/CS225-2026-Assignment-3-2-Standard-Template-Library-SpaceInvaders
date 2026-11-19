#pragma once
#include "src/Framework/event.hh"

enum Input
{
    MoveLeft,
    MoveRight,
    Still,
    Shoot
};

enum colType
{
    AlienPlayer,
    AlienWall,
    BulletPLayer
};

class inputEvent : public Event
{
public:
    Input mInput;

    inputEvent(Input input) : mInput(input) {}
};

class collisionEvent : public Event
{
public:
    colType collisionType;
    collisionEvent(colType type) : collisionType(type) {}
};