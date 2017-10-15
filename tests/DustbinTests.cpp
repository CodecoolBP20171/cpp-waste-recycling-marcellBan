#include "../include/Garbage.h"

#include "gtest/gtest.h"

namespace {
    // tests go here
    TEST(GarbageTest, NameTest){
        auto hi = const_cast<char*>("Hello");
        auto g = Garbage(hi);
        EXPECT_STREQ(hi, g.getName().c_str());
    }
}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}