#pragma once

#include <functional>
#include <any>
#include <assert.h>
#include <string>

using Msg = std::any;
using EventHandler = std::function<Msg const(Msg const msg)>;

class Hsm;

enum class StdEvents
{
    START,
    ENTRY,
    EXIT
};


class State {
  public:

    State(const std::string &name, State *super, EventHandler eventHandler);

  private:
    Msg const onEvent(Msg const msg)
    {
        return eventHandler(msg);
    }

    EventHandler eventHandler;
    State *super;
    std::string const &name;

    friend Hsm;
};

class Hsm {
    std::string const &name;
    State *curr;
protected:
    State *next;                  /* next state (non 0 if transition taken) */
    State *source;                   /* source state during last transition */
    State top;                                     /* top-most state object */
public:
    Hsm(std::string const &name, EventHandler topHndlr);
    void onStart();
    void onEvent(Msg const msg);
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
