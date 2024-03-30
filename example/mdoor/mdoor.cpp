#include "mdoor.h"
#include <memory>


Door::Door() : Hsm("Door")
{
    auto opened = std::make_shared<State>("Opened", nullptr, [&] (auto event){openedStd(event);});
    auto closed = std::make_shared<State>("Closed", nullptr, [&] (auto event){closedStd(event);});
    auto locked = std::make_shared<State>("Locked", closed, [&] (auto event) {lockedStd(event);});

    auto states = {closed, opened,  locked};
    auto transitions = {
        Transition{opened, &CLOSE, closed},
        Transition{closed, &OPEN, opened},
        Transition{closed, &LOCK, locked},
        Transition{closed, &KNOCK, closed, [&] { closed_knock();}}
    };
    activate(states, transitions);
}

void Door::open()
{
    onEvent(&OPEN);
}

void Door::close()
{
    onEvent(&CLOSE);
}

void Door::lock()
{
    onEvent(&LOCK);
}

void Door::knock()
{
    onEvent(&KNOCK);
}


void Door::closed_knock()
{
    doorsign = "Just open the door";
}


auto Door::readDoorSign() -> std::string
{
    return doorsign;
}

void Door::closedStd(StdEvents event)
{
    switch (event)
    {
    case StdEvents::ENTRY:
        doorsign = "Knock to open";
        break;

    default:
        break;
    }
}

void Door::lockedStd(StdEvents event)
{
    switch (event)
    {
    case StdEvents::ENTRY:
        doorsign = "Come back later";
        break;

    default:
        break;
    }
}


void Door::openedStd(StdEvents event)
{
    switch (event)
    {
    case StdEvents::START:
        doorsign = "Come on in";
        break;

    default:
        break;
    }
}
