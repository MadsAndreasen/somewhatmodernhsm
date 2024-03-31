#include "mdoor.h"
#include "hsm.h"
#include <memory>
#include <optional>


Door::Door() : Hsm("Door")
{
    auto opened = std::make_shared<State>("Opened", nullptr, [&] (auto event){openedStd(event);});
    auto closed = std::make_shared<State>("Closed", nullptr, [&] (auto event){closedStd(event);});
    auto locked = std::make_shared<State>("Locked", closed, [&] (auto event) {lockedStd(event);});

    auto doorStates = {closed, opened,  locked};
    auto doorTransitions = {
        Transition{opened, &CLOSE, closed, std::nullopt},
        Transition{closed, &OPEN, opened, std::nullopt},
        Transition{closed, &LOCK, locked, std::nullopt},
        Transition{closed, &KNOCK, closed, [&] { closed_knock();}}
    };
    activate(doorStates, doorTransitions);
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
    if (event == StdEvents::ENTRY)
    {
        doorsign = "Knock to open";
    }
}

void Door::lockedStd(StdEvents event)
{
    if (event == StdEvents::ENTRY)
    {
        doorsign = "Come back later";
    }
}


void Door::openedStd(StdEvents event)
{
    if (event == StdEvents::START)
    {
        doorsign = "Come on in";
    }
}
