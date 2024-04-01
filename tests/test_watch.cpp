#include "gtest/gtest.h"
#include "watch.h"
#include <chrono>

using namespace std::chrono_literals;
// NOLINTNEXTLINE
TEST(modern, sunshine_watch_test)
{
    auto now = std::chrono::system_clock::now();
    Watch watch;

    watch.some_time_passed();
    auto time = watch.get_time();

    auto now_in_minutes = std::chrono::duration_cast<std::chrono::minutes>(now.time_since_epoch());
    auto time_in_minutes = std::chrono::duration_cast<std::chrono::minutes>(time.time_since_epoch());

    ASSERT_EQ(time_in_minutes, now_in_minutes + 1min);

    ASSERT_EQ(watch.view(), "Time");

    watch.press_mode();
    ASSERT_EQ(watch.view(), "Date");
    watch.press_mode();
    ASSERT_EQ(watch.view(), "Time");

    watch.press_set();
    ASSERT_EQ(watch.view(), "Setting");
    watch.press_set();
    watch.press_set();
    watch.press_set();
    watch.press_set();
    ASSERT_EQ(watch.view(), "Time");
    time = watch.get_time();
    time_in_minutes = std::chrono::duration_cast<std::chrono::minutes>(time.time_since_epoch());

    watch.press_set();
    watch.press_mode();
    watch.press_set();
    watch.press_set();
    watch.press_set();
    watch.press_set();
    ASSERT_EQ(watch.view(), "Time");
    auto new_time = watch.get_time();

    auto new_time_in_minutes = std::chrono::duration_cast<std::chrono::minutes>(new_time.time_since_epoch());
    ASSERT_EQ(time_in_minutes + 1h, new_time_in_minutes);

}


auto main(int argc, char **argv) -> int
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
