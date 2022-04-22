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

protected:
  State world, house, hall, kitchen, garden, frontGarden, well;
  Event NORTH, EAST, SOUTH, WEST;
  Event SMELL, EAT;

private:
  void noAction(StdEvents event);
  void houseAction(StdEvents event);
  void gardenAction(StdEvents event);
  void startStd(StdEvents event);
  void hallAction(StdEvents event);
  void kitchenAction(StdEvents event);
  void frontGardenAction(StdEvents event);
  void wellAction(StdEvents event);

  void getHungry();
  void eat();
};
