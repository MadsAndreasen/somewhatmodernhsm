#include "wizard.h"

#include <iostream>


WizardsWorld::WizardsWorld() : Hsm("WizardsWorld")
{
    auto house = std::make_shared<State>("house", nullptr, [&] (auto event){houseAction(event);});
    auto hall = std::make_shared<State>("hall", house, [&] (auto event){hallAction(event);});
    auto kitchen = std::make_shared<State>("kitchen", house, [&] (auto event){kitchenAction(event);});
    auto garden = std::make_shared<State>("garden", nullptr, [&] (auto event){gardenAction(event);});
    auto frontGarden = std::make_shared<State>("frontGarden", garden, [&] (auto event){frontGardenAction(event);});
    auto well = std::make_shared<State>("well", garden, [&] (auto event){wellAction(event);});

    auto states = {frontGarden, house, hall, kitchen, garden,well};
    auto transitions = {
        Transition{frontGarden, &NORTH, hall},
        Transition{frontGarden, &WEST, well},
        Transition{hall, &NORTH, kitchen},
        Transition{hall, &SOUTH, frontGarden},
        Transition{kitchen, &SOUTH, hall},
        Transition{kitchen, &SMELL, kitchen, [&]() { getHungry(); }},
        Transition{kitchen, &EAT, kitchen, [&]() { eat(); }},
        Transition{well, &EAST, frontGarden}
    };
    activate(states, transitions);
}

void WizardsWorld::north()
{
    onEvent(&NORTH);
}

void WizardsWorld::east()
{
    onEvent(&EAST);
}

void WizardsWorld::south()
{
    onEvent(&SOUTH);
}

void WizardsWorld::west()
{
    onEvent(&WEST);
}

void WizardsWorld::smell()
{
    onEvent(&SMELL);
}

void WizardsWorld::take()
{
    onEvent(&EAT);
}

void WizardsWorld::noAction(StdEvents event)
{

}

void WizardsWorld::houseAction(StdEvents event)
{
    if(StdEvents::ENTRY == event) {
        std::cout << "You are cursed with a magic spell" << '\n';
    }
    if(StdEvents::EXIT == event) {
        std::cout << "The magic spell is removed from you" << '\n';
    }
}

void WizardsWorld::gardenAction(StdEvents event)
{

}

void WizardsWorld::hallAction(StdEvents event)
{
    if(StdEvents::START == event)
    {
        std::cout << "The wizard's hall is small and smelly" << '\n';
    }
}

void WizardsWorld::kitchenAction(StdEvents event)
{
    if(StdEvents::START == event)
    {
        std::cout << "The kitchen is a complete mess!" << '\n';
    }
}

void WizardsWorld::frontGardenAction(StdEvents event)
{
    if(StdEvents::START == event)
    {
        std::cout << "You are standing in the wizard's front garden" << '\n';
    }
}

void WizardsWorld::wellAction(StdEvents event)
{
    if(StdEvents::START == event)
    {
        std::cout << "The water in the well does not look clean" << '\n';
    }
}

void WizardsWorld::getHungry()
{
    std::cout << "The kitchen smells nice and you get hungry" << '\n';
}

void WizardsWorld::eat()
{
    std::cout << "You eat some slimy stuff from the table" << '\n';
}
