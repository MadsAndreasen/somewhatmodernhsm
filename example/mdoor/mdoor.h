#pragma once

#include "hsm.h"


class Door : public Hsm {
public:
  Door();
  void open();
  void close();
  void lock();
  void knock();

  auto readDoorSign() -> std::string;

private:
  Event OPEN{}, CLOSE{}, LOCK{}, KNOCK{};

  void startStd(StdEvents event);
  void closedStd(StdEvents event);
  void openedStd(StdEvents event);
  void lockedStd(StdEvents event);

  void closed_knock();

  std::string doorsign{};

};
