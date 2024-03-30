#include "hsm.h"


class WizardsWorld : public Hsm {
public:
  WizardsWorld();
  void north();
  void east();
  void south();
  void west();
  void smell();
  void take();

private:
  Event NORTH, EAST, SOUTH, WEST;
  Event SMELL, EAT;

  void noAction(StdEvents event);
  static void houseAction(StdEvents event);
  void gardenAction(StdEvents event);
  void startStd(StdEvents event);
  static void hallAction(StdEvents event);
  static void kitchenAction(StdEvents event);
  static void frontGardenAction(StdEvents event);
  static void wellAction(StdEvents event);

  static void getHungry();
  static void eat();
};
