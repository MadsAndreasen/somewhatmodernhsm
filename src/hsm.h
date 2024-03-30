#pragma once

#include <ctime>
#include <functional>
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
            m_event = std::rand(); //NOLINT
        };

        auto operator==(Event const &other) const -> bool
        {
            return m_event == other.m_event;
        }

    private:
        int m_event;

};


struct Transition
{
    State *from;
    Event const *event;
    State *to;
    EventHandler eventHandler;
};


class State
{
    public:
        State(std::string name, State *parent, std::function<void(StdEvents)> standardEventHandler);

    private:
        std::string name;
        State *parent;

        std::function<void(StdEvents)> handleStandardEvents;

        friend Hsm;
};

class Hsm
{
    public:
        Hsm(std::string const &name, State *start);

        void enable();
        void transitionTo(State *target);
        void onEvent(Event const *event);

        std::vector<Transition> transitions {};
    private:

        void entry(State *target);
        void exit(State *target);
        auto findCommonParent(State *other) -> State *;

        std::string name;
        State *start;
        State *currentState = nullptr;


};
