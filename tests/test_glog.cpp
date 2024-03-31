#include "gtest/gtest.h"
#include "glog/logging.h"

// NOLINTNEXTLINE
TEST(sampletestCase, sampleTest)
{
    LOG(INFO) << "Hello, GLOG!";
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
