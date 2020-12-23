#include "hsm.h"

#include <stack>
#include <stdexcept>

Hsm::Hsm(std::string const &name, State *start)
    : name(name), start(start)
{

}

void Hsm::onEvent(Event const *event)
{
    for (auto iterator = currentState; iterator != nullptr; iterator = iterator->parent)
    {
        for (auto &transition : transitions)
        {
            if ((transition.event->event == event->event) && (transition.from == iterator))
            {
                if (transition.to == transition.from)
                {
                    transition.eventHandler();
                }
                else
                {
                    transitionTo(transition.to);
                }

                break;
            }
        }
    }
}

void Hsm::enable()
{
    currentState = start;
    start->handleStandardEvents(StdEvents::ENTRY);
    start->handleStandardEvents(StdEvents::START);
}

void Hsm::transitionTo(State *target)
{
    exit(target);
    entry(target);
    currentState = target;
}

void Hsm::exit(State *target)
{
    State *commonParent = findCommonParent(target);
    for (auto iterator = currentState; iterator != commonParent; iterator = iterator->parent)
    {
        iterator->handleStandardEvents(StdEvents::EXIT);
    }
}

State *Hsm::findCommonParent(State *other)
{
    for (auto source = currentState; source != nullptr; source = source->parent)
    {
        for (auto target = other; target != nullptr; target = target->parent)
        {
            if (source == target)
            {
                return source;
            }
        }
    }
    throw std::logic_error("No common parent - " + currentState->name + " - " + other->name);
}

void Hsm::entry(State *target)
{
    State *commonParent = findCommonParent(target);

    auto currentStep = target;
    std::stack<State*> trace;
    for(auto currentStep = target; currentStep != commonParent; currentStep = currentStep->parent)
    {
        trace.push(currentStep);
    }
    while (!trace.empty())
    {
        auto current = trace.top();
        current->handleStandardEvents(StdEvents::ENTRY);
        trace.pop();
    }

}

State::State(std::string const name, State *parent, std::function<void(StdEvents)> standardEventHandler)
: name(name), parent(parent), handleStandardEvents(standardEventHandler)
{

}


int Event::count = 0;
