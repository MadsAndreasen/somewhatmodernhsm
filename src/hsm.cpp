#include "hsm.h"

static Msg const startMsg = StdEvents::START;
static Msg const entryMsg = StdEvents::ENTRY;
static Msg const exitMsg  = StdEvents::EXIT;

#define MAX_STATE_NESTING 8

/* State Ctor...............................................................*/
State::State(std::string const &n, State *s, EventHandler h)
        : name(n), super(s), eventHandler(h)
{}

/* Hsm Ctor.................................................................*/
Hsm::Hsm(std::string const &n, EventHandler topHndlr)
        : top("top", 0, topHndlr), name(n)
{}

/* enter and start the top state............................................*/
void Hsm::onStart() {
    curr = &top;
    next = 0;
    curr->onEvent(entryMsg);
    while (curr->onEvent(startMsg), next) {
        State *entryPath[MAX_STATE_NESTING];
        State **trace = entryPath;
        State *s;
        *trace = 0;
        for (s = next; s != curr; s = s->super) {
            *(++trace) = s;                         /* trace path to target */
        }
        while (s = *trace--) {                 /* retrace entry from source */
            s->onEvent(entryMsg);
        }
        curr = next;
        next = 0;
    }
}

/* state machine "engine"...................................................*/
void Hsm::onEvent(Msg const msg) {
    State *entryPath[MAX_STATE_NESTING];
    State **trace;
    State *s;
    for (s = curr; s; s = s->super) {
        source = s;                     /* level of outermost event handler */
        auto unhandled = s->onEvent(msg);
        if (unhandled.type() == typeid(handled)) {                                       /* processed? */
            if (next) {                          /* state transition taken? */
                trace = entryPath;
                *trace = 0;
                for (s = next; s != curr; s = s->super) {
                    *(++trace) = s;                 /* trace path to target */
                }
                while (s = *trace--) {            /* retrace entry from LCA */
                    s->onEvent(entryMsg);
                }
                curr = next;
                next = 0;
                while (curr->onEvent(startMsg), next) {
                    trace = entryPath;
                    *trace = 0;
                    for (s = next; s != curr; s = s->super) {
                        *(++trace) = s;            /* record path to target */
                    }
                    while (s = *trace--) {             /* retrace the entry */
                        s->onEvent(entryMsg);
                    }
                    curr = next;
                    next = 0;
                }
            }
            break;                                       /* event processed */
        }
    }
}

/* exit current states and all superstates up to LCA .......................*/
void Hsm::exit_(unsigned char toLca) {
    State *s = curr;
    while (s != source) {
        s->onEvent(exitMsg);
        s = s->super;
    }
    while (toLca--) {
        s->onEvent(exitMsg);
        s = s->super;
    }
    curr = s;
}

/* find # of levels to Least Common Ancestor................................*/
unsigned char Hsm::toLCA_(State *target) {
    State *s, *t;
    unsigned char toLca = 0;
    if (source == target) {
        return 1;
    }
    for (s = source; s; ++toLca, s = s->super) {
        for (t = target; t; t = t->super) {
            if (s == t) {
                return toLca;
            }
        }
    }
    return 0;
}
