#include "hsm.h"


class Door : public Hsm {
public:
  Door();
  void open();
  void close();
  void lock();
  void knock();

  std::string readDoorSign();

private:
  State start, opened, closed, locked;
  Event OPEN, CLOSE, LOCK, KNOCK;

  void startStd(StdEvents event);
  void closedStd(StdEvents event);
  void openedStd(StdEvents event);
  void lockedStd(StdEvents event);

  void closed_knock();

  std::string doorsign;

};
