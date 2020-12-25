#pragma once

#include <any>
#include <functional>
#include <string>
#include <memory>

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
            event = count++;
        };

        int event;
    private:
        static int count;

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
        State(std::string const name, State *parent, std::function<void(StdEvents)> standardEventHandler);

    private:
        std::string const name;
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
        State *findCommonParent(State *other);

        std::string const &name;
        State *start;
        State *currentState = nullptr;


};
