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

private:
  void startStd(StdEvents event);
  void closedStd(StdEvents event);
  void openedStd(StdEvents event);
  void lockedStd(StdEvents event);

  void closed_knock();

  std::string doorsign = "";

};

enum class Events {
    OPEN,
    CLOSE,
    LOCK,
    UNLOCK,
};
