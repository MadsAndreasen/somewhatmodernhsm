#include "hsm.h"

#include <stack>
#include <stdexcept>

Hsm::Hsm(std::string const &name, State *start)
    : name(name), start(start)
{

}

void Hsm::onEvent(Event const *event)
{
    for (auto* iterator = currentState; iterator != nullptr; iterator = iterator->parent)
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
    currentState->handleStandardEvents(StdEvents::START);
}

void Hsm::exit(State *target)
{
    State *commonParent = findCommonParent(target);
    for (auto* iterator = currentState; iterator != commonParent; iterator = iterator->parent)
    {
        iterator->handleStandardEvents(StdEvents::EXIT);
    }
}

auto Hsm::findCommonParent(State *other) -> State*
{
    for (auto* source = currentState; source != nullptr; source = source->parent)
    {
        for (auto* target = other; target != nullptr; target = target->parent)
        {
            if (source == target)
            {
                return source;
            }
        }
    }

    auto currentName = (currentState != nullptr) ? currentState->name : "";
    auto otherName = (other != nullptr) ? other->name : "";
    throw std::logic_error("No common parent - " + currentName + " - " + otherName);
}

void Hsm::entry(State *target)
{
    State *commonParent = findCommonParent(target);

    std::stack<State*> trace;
    for(auto* currentStep = target; currentStep != commonParent; currentStep = currentStep->parent)
    {
        trace.push(currentStep);
    }
    while (!trace.empty())
    {
        auto* current = trace.top();
        current->handleStandardEvents(StdEvents::ENTRY);
        trace.pop();
    }

}

State::State(std::string name, State *parent, std::function<void(StdEvents)> standardEventHandler)
: name(std::move(name)), parent(parent), handleStandardEvents(std::move(standardEventHandler))
{

}


int Event::count = 0;
