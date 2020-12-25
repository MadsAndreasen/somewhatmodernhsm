#include "hsm.h"


class Door : public Hsm {
public:
  Door();
  void open();
  void close();
  void lock();
  void knock();

  std::string readDoorSign();

protected:
  State start, opened, closed, locked;
  Event OPEN, CLOSE, LOCK, KNOCK;

private:
  void startStd(StdEvents event);
  void closedStd(StdEvents event);
  void openedStd(StdEvents event);
  void lockedStd(StdEvents event);

  void closed_knock();

  std::string doorsign = "";

};
