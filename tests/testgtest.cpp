#include "gtest/gtest.h"

// NOLINTNEXTLINE
TEST(sampletestCase, sampleTest)
{
    EXPECT_EQ(1, 1);
}


auto main(int argc, char **argv) -> int
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
