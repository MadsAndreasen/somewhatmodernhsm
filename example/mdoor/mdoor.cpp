#include <iostream>
#include <cstddef>
#include "mdoor.h"



using namespace std::placeholders;

namespace
{
    Event OPEN, CLOSE, LOCK, KNOCK;
}

Door::Door() : Hsm("Door", &start),
    start("Start", nullptr, std::bind(&Door::startStd, this, _1)),
    opened("Openend", &start, std::bind(&Door::openedStd, this, _1)),
    closed("Closed", &start, std::bind(&Door::closedStd, this, _1)),
    locked("Locked", &closed, std::bind(&Door::lockedStd, this, _1))
{
    transitions = std::vector<Transition>{
        Transition{&opened, &CLOSE, &closed},
        Transition{&closed, &OPEN, &opened},
        Transition{&closed, &LOCK, &locked},
        Transition{&closed, &KNOCK, &closed, std::bind(&Door::closed_knock, this)}
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


std::string Door::readDoorSign()
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
