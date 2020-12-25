#include "mdoor.h"

#include <cstddef>
#include <iostream>


Door::Door() : Hsm("Door", &start),
    start("Start", nullptr, [&] (auto event){startStd(event);}),
    opened("Openend", &start, [&] (auto event){openedStd(event);}),
    closed("Closed", &start, [&] (auto event){closedStd(event);}),
    locked("Locked", &closed, [&] (auto event) {lockedStd(event);})
{
    transitions = std::vector<Transition>{
        Transition{&opened, &CLOSE, &closed},
        Transition{&closed, &OPEN, &opened},
        Transition{&closed, &LOCK, &locked},
        Transition{&closed, &KNOCK, &closed, [&] { closed_knock();}}
    };
    enable();
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

void Door::startStd(StdEvents event)
{
    switch (event)
    {
    case StdEvents::START:
        transitionTo(&closed);
        break;
    case StdEvents::ENTRY:
        doorsign = "Door is beeing built";
        break;
    default:
        break;
    }
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
    case StdEvents::ENTRY:
        doorsign = "Come on in";
        break;

    default:
        break;
    }
}
