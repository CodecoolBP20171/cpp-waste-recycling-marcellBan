#include "gtest/gtest.h"
#include "../include/dustbin/Dustbin.h"
#include "../include/dustbin/DustbinErrors.hpp"

namespace {
    // test fixture class
    class DustbinTest : public ::testing::Test {
    protected:
        Dustbin db;
        std::unique_ptr<Garbage> houseWaste;
        std::unique_ptr<PaperGarbage> paperGarbage;
        std::unique_ptr<PlasticGarbage> plasticGarbage;

        DustbinTest()
                : db("white"),
                  houseWaste(new Garbage("food remains")),
                  paperGarbage(new PaperGarbage("news paper")),
                  plasticGarbage(new PlasticGarbage("bottle")) {}

        virtual ~DustbinTest() {}
    };

    // tests
    TEST(GarbageTest, NameTest) {
        auto hi = const_cast<char*>("Hello");
        auto g = Garbage(hi);
        EXPECT_STREQ(hi, g.getName().c_str());
    }

    TEST_F(DustbinTest, ColorTest) {
        auto color = const_cast<char*>("white");
        EXPECT_STREQ(color, db.getColor().c_str());
    }

    TEST_F(DustbinTest, AddingAllTypesOfGarbage) {
        paperGarbage->squeeze();
        plasticGarbage->clean();

        EXPECT_NO_THROW(db.throwOutGarbage(houseWaste));
        EXPECT_EQ(1, db.getGarbageCount());
        EXPECT_NO_THROW(db.throwOutPaperGarbage(paperGarbage));
        EXPECT_EQ(1, db.getPaperCount());
        EXPECT_NO_THROW(db.throwOutPlasticGarbage(plasticGarbage));
        EXPECT_EQ(1, db.getPlasticCount());
    }

    TEST_F(DustbinTest, EmptyDustbin) {
        EXPECT_NO_THROW(db.throwOutGarbage(houseWaste));
        EXPECT_EQ(1, db.getGarbageCount());
        EXPECT_NO_THROW(db.emptyContents());
        EXPECT_TRUE(db.isEmpty());
    }

    TEST_F(DustbinTest, AutomaticExpansion) {
        for (auto i = 0; i < 10; ++i) {
            auto garbage = std::unique_ptr<Garbage>(new Garbage(std::to_string(i)));
            auto paGarbage = std::unique_ptr<PaperGarbage>(new PaperGarbage(std::to_string(i)));
            auto plGarbage = std::unique_ptr<PlasticGarbage>(new PlasticGarbage(std::to_string(i)));
            paGarbage->squeeze();
            plGarbage->clean();
            db.throwOutGarbage(garbage);
            db.throwOutPaperGarbage(paGarbage);
            db.throwOutPlasticGarbage(plGarbage);
        }
        auto baseCap = Dustbin::INITIAL_CAPACITY;
        EXPECT_EQ(baseCap, db.getCurrentGarbageCapacity());
        EXPECT_EQ(baseCap, db.getCurrentPaperCapacity());
        EXPECT_EQ(baseCap, db.getCurrentPlasticCapacity());
        paperGarbage->squeeze();
        plasticGarbage->clean();
        db.throwOutGarbage(houseWaste);
        db.throwOutPaperGarbage(paperGarbage);
        db.throwOutPlasticGarbage(plasticGarbage);
        auto extendedCap = Dustbin::INITIAL_CAPACITY + Dustbin::CAPACITY_STEP;
        EXPECT_EQ(extendedCap, db.getCurrentGarbageCapacity());
        EXPECT_EQ(extendedCap, db.getCurrentPaperCapacity());
        EXPECT_EQ(extendedCap, db.getCurrentPlasticCapacity());
    }

    TEST_F(DustbinTest, ContentErrors) {
        EXPECT_THROW(db.throwOutPaperGarbage(paperGarbage), DustbinContentError);
        EXPECT_THROW(db.throwOutPlasticGarbage(plasticGarbage), DustbinContentError);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}