#pragma once
#include "src/Framework/event_handlers.hh"

class inputEventManager : public EventManager
{
public:
    void update() override;
};