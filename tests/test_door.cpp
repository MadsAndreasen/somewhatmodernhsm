#include "gtest/gtest.h"
#include "door.h"

TEST(simple, door_test)
{
    Door door;
    door.onStart();

    door.open();
    door.close();
    door.lock();

}
