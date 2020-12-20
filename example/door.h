#include "hsm.h"

class Door : public Hsm {
  int tsec, tmin, thour, dday, dmonth;
protected:
  State opened, closed, locked;
public:
  Door();
  Msg const topHndlr(Msg const msg);
  Msg const openedHndlr(Msg const msg);
  Msg const closedHndlr(Msg const msg);
  Msg const lockedHndlr(Msg const msg);
  void open();
  void close();
  void lock();
};

enum class Events {
    OPEN,
    CLOSE,
    LOCK,
    UNLOCK,
};
