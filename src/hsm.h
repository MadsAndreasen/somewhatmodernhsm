#pragma once

#include <ctime>
#include <functional>
#include <memory>
#include <string>
#include <vector>

using EventHandler = std::function<void(void)>;

class Hsm;
class State;

enum class StdEvents
{
    ENTRY,
    START,
    EXIT
};

class Event
{
    public:
        Event()
        {
            std::srand(std::time(nullptr)); //NOLINT - Don't complain about the seed value
            event_id = std::rand(); //NOLINT
        };

        auto operator==(Event const &other) const -> bool
        {
            return event_id == other.event_id;
        }

    private:
        int event_id;

};


struct Transition
{
    std::shared_ptr<State> from;
    Event const *event;
    std::shared_ptr<State> to;
    EventHandler eventHandler;
};


class State
{
    public:
        State(std::string name, std::shared_ptr<State>parent, std::function<void(StdEvents)> standardEventHandler);

    private:
        std::string name;
        std::shared_ptr<State> parent;

        std::function<void(StdEvents)> handleStandardEvents;

        friend Hsm;
};

class Hsm
{
    public:
        explicit Hsm(std::string name);

        void activate(std::vector<std::shared_ptr<State>> states, std::vector<Transition> transitions);

    protected:
        void onEvent(Event const *event);

    private:
        void transitionTo(std::shared_ptr<State> const &target);
        void onEvent(StdEvents event);
        void entry(std::shared_ptr<State> const &target);
        void exit(std::shared_ptr<State> const &target);
        auto findCommonParent(std::shared_ptr<State> const &other) -> std::shared_ptr<State>;

        std::vector<Transition> transitions {};
        std::vector<std::shared_ptr<State>> states {};
        std::string name;
        std::shared_ptr<State> currentState = nullptr;
};
