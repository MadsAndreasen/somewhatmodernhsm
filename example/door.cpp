#include <assert.h>
#include <stdio.h>
#include <iostream>
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
};

enum class Events {
    OPEN,
    CLOSE,
    LOCK,
    UNLOCK,
};


Msg const Door::topHndlr(Msg const msg) {
  if (msg.type() == typeid(StdEvents))
  {
    auto event = std::any_cast<StdEvents>(msg);
    switch (event)
    {
    case StdEvents::START:
      STATE_START(&closed);
      return Hsm::handled;
    }

  }
  return msg;
}

Msg const Door::openedHndlr(Msg const msg) {
  if (msg.type() == typeid(StdEvents))
  {
    auto event = std::any_cast<StdEvents>(msg);
    switch (event)
    {
    case StdEvents::START:
      std::cout << "Opened" << std::endl;
      return Hsm::handled;
    }

  }
  else
  {
    auto event = std::any_cast<Events>(msg);
    switch (event)
    {
    case Events::CLOSE:
      std::cout << "Closing" << std::endl;
      STATE_TRAN(&closed);
      return Hsm::handled;
    }
  }

  return msg;
}

Msg const Door::closedHndlr(Msg const msg) {
  if (msg.type() == typeid(StdEvents))
  {
    auto event = std::any_cast<StdEvents>(msg);
    switch (event)
    {
    case StdEvents::START:
      std::cout << "Closed" << std::endl;
      return Hsm::handled;
    }

  }
  else
  {
    auto event = std::any_cast<Events>(msg);
    switch (event)
    {
    case Events::OPEN:
      std::cout << "Opening" << std::endl;
      STATE_TRAN(&opened);
      return Hsm::handled;
    case Events::LOCK:
      std::cout << "Locking" << std::endl;
      STATE_TRAN(&locked);
      return Hsm::handled;
    }
  }

  return msg;
}


Msg const Door::lockedHndlr(Msg const msg) {
  if (msg.type() == typeid(StdEvents))
  {
    auto event = std::any_cast<StdEvents>(msg);
    switch (event)
    {
    case StdEvents::START:
      std::cout << "Locked" << std::endl;
      return handled;
    }

  }
  else
  {
    auto event = std::any_cast<Events>(msg);
    switch (event)
    {
    case Events::UNLOCK:
      std::cout << "Unlocking" << std::endl;
      STATE_TRAN(&locked);
      return handled;
    }
  }

  return msg;
}


using namespace std::placeholders;


Door::Door() : Hsm("Door", std::bind(&Door::topHndlr, this, _1)),
  opened("opened", &top, std::bind(&Door::openedHndlr, this, _1)),
  closed("closed", &top, std::bind(&Door::closedHndlr, this, _1)),
  locked("locked", &closed, std::bind(&Door::lockedHndlr, this, _1))
{
}

int main() {
  Door watch;
  watch.onStart();
  for (;;)  {
    int i;
    printf("\nEvent<-");
    scanf("%d", &i);
    watch.onEvent(static_cast<Events>(i));
  }
  return 0;
}