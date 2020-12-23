#include "gtest/gtest.h"
#include "mdoor.h"

TEST(modern, sunshine_door_test)
{
    Door door;

    EXPECT_EQ("Knock to open", door.readDoorSign());

    door.open();
    EXPECT_EQ("Come on in", door.readDoorSign());

    door.close();
    EXPECT_EQ("Knock to open", door.readDoorSign());

    door.lock();
    EXPECT_EQ("Come back later", door.readDoorSign());

}


TEST(modern, cannot_lock_open_door)
{
    Door door;

    door.open();
    EXPECT_EQ("Come on in", door.readDoorSign());

    door.lock();
    EXPECT_EQ("Come on in", door.readDoorSign());

}


TEST(modern, open_closed_door)
{
    Door door;


    door.lock();

    door.open();
    EXPECT_EQ("Come on in", door.readDoorSign());

}


TEST(modern, knock_on_closed)
{
    Door door;

    door.knock();
    EXPECT_EQ("Just open the door", door.readDoorSign());

    door.open();
    EXPECT_EQ("Come on in", door.readDoorSign());
}
