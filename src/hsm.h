#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <random>
#include <string>
#include <sys/types.h>
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
        Event() : event_id(std::default_random_engine{std::random_device{}()}())
        {

        }

        auto operator==(Event const &other) const -> bool
        {
            return event_id == other.event_id;
        }

    private:
        u_int64_t event_id = 0;

};


struct Transition
{
    std::shared_ptr<State> from;
    Event const *event;
    std::shared_ptr<State> to;
    std::optional<EventHandler> eventHandler;
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
