#pragma once

#include <functional>
#include <any>
#include <assert.h>

using Msg = std::any;
using EvtHndlr = std::function<Msg const(Msg const msg)>;

class Hsm;

class State {
  public:

    State(char const *name, State *super, EvtHndlr hndlr);

  private:
    Msg const onEvent(Msg const msg) {
        return hndlr(msg);
    }

    EvtHndlr hndlr;/* state's handler function */
    State *super;
    char const *name;

    friend Hsm;
};

class Hsm {                        /* Hierarchical State Machine base class */
    char const *name;                             /* pointer to static name */
    State *curr;                                           /* current state */
protected:
    State *next;                  /* next state (non 0 if transition taken) */
    State *source;                   /* source state during last transition */
    State top;                                     /* top-most state object */
public:
    Hsm(char const *name, EvtHndlr topHndlr);                       /* Ctor */
    void onStart();                        /* enter and start the top state */
    void onEvent(Msg const msg);                 /* "state machine engine" */
    static constexpr std::nullptr_t handled{};
protected:
    unsigned char toLCA_(State *target);
    void exit_(unsigned char toLca);
    State *STATE_CURR() { return curr; }
    void STATE_START(State *target) {
        assert(next == 0);
        next = target;
    }
# define STATE_TRAN(target_) if (1) { \
    static unsigned char toLca_ = 0xFF; \
    assert(next == 0); \
    if (toLca_ == 0xFF) \
        toLca_ = toLCA_(target_); \
    exit_(toLca_); \
    next = (target_); \
} else ((void)0)
};


enum class StdEvents
{
    START,
    ENTRY,
    EXIT,
    HANDLED,
};

// #define START_EVT ((Event)(-1))
// #define ENTRY_EVT ((Event)(-2))
// #define EXIT_EVT  ((Event)(-3))
