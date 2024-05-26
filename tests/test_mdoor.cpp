#include "gtest/gtest.h"
#include "mdoor.h"

#include <cstdlib>
#include <new>

static size_t malloc_count = 0;

void* operator new(size_t size) {
    malloc_count++;
    return std::malloc(size);
}

void operator delete(void* ptr) noexcept {
    std::free(ptr);
}

// Rest of your code...
// NOLINTNEXTLINE
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

// NOLINTNEXTLINE
TEST(modern, cannot_lock_open_door)
{
    Door door;

    auto current_malloc = malloc_count;

    door.open();
    EXPECT_EQ(current_malloc, malloc_count);
    EXPECT_EQ("Come on in", door.readDoorSign());

    door.lock();
    EXPECT_EQ("Come on in", door.readDoorSign());

}

// NOLINTNEXTLINE
TEST(modern, open_closed_door)
{
    Door door;


    door.lock();

    door.open();
    EXPECT_EQ("Come on in", door.readDoorSign());

}

// NOLINTNEXTLINE
TEST(modern, knock_on_closed)
{
    Door door;

    door.knock();
    EXPECT_EQ("Just open the door", door.readDoorSign());

    door.open();
    EXPECT_EQ("Come on in", door.readDoorSign());
}


auto main(int argc, char **argv) -> int {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
