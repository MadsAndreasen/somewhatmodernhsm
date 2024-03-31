#include "hsm.h"

#include <memory>
#include <stack>
#include <utility>
#include <vector>

Hsm::Hsm(std::string name)
    : name(std::move(name))
{

}

void Hsm::onEvent(Event const *event)
{
    for (auto iterator = currentState; iterator != nullptr; iterator = iterator->parent)
    {
        for (auto &transition : transitions)
        {
            if ((transition.event == event) && (transition.from == iterator))
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

void Hsm::onEvent(StdEvents event)
{
    currentState->handleStandardEvents(event);
}

void Hsm::activate(std::vector<std::shared_ptr<State>> states, std::vector<Transition> transitions)
{
    this->transitions = std::move(transitions);
    this->states = std::move(states);
    currentState = this->states.at(0);

    onEvent(StdEvents::ENTRY);
    onEvent(StdEvents::START);
}

void Hsm::transitionTo(std::shared_ptr<State> const &target)
{
    exit(target);
    entry(target);
    currentState = target;
    currentState->handleStandardEvents(StdEvents::START);
}

void Hsm::exit(std::shared_ptr<State> const &target)
{
    auto commonParent = findCommonParent(target);
    for (auto iterator = currentState; iterator != commonParent; iterator = iterator->parent)
    {
        iterator->handleStandardEvents(StdEvents::EXIT);
    }
}

auto Hsm::findCommonParent(std::shared_ptr<State> const &other) -> std::shared_ptr<State>
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
    return nullptr;
}

void Hsm::entry(std::shared_ptr<State> const &target)
{
    auto commonParent = findCommonParent(target);

    std::stack<std::shared_ptr<State>> trace;
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

State::State(std::string name, std::shared_ptr<State> parent, std::function<void(StdEvents)> standardEventHandler)
: name(std::move(name)), parent(std::move(parent)), handleStandardEvents(std::move(standardEventHandler))
{

}
