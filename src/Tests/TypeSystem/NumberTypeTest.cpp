//
// Created by caedus on 20.02.2021.
//

#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "TypeSystem/Types/NumberObject.hpp"
#include "TypeSystem/Types/StringObject.hpp"
#include "TypeSystem/Types/TypeSystemError.hpp"

namespace nastya::typesystem {

TEST(NumberTypeTest, testConstructor)
{
    NumberObject object;
    EXPECT_EQ(object.getInteger(), 0);
    EXPECT_EQ(object.getNumberType(), NumberType::Integer);
    EXPECT_TRUE(object.isComparable());

    int integer_test_case = 132;
    NumberObject integer_object(integer_test_case);
    EXPECT_EQ(integer_object.getInteger(), integer_test_case);
    EXPECT_EQ(integer_object.getType(), ObjectType::Number);
    EXPECT_EQ(integer_object.getNumberType(), NumberType::Integer);
    EXPECT_EQ(integer_object.info(), "Integer => " + std::to_string(integer_test_case));
    EXPECT_TRUE(object.isComparable());

    float floating_test_case = 0.12345;
    std::stringstream ss;
    ss << "Floating => " << floating_test_case;
    NumberObject floating_object(floating_test_case);
    EXPECT_EQ(floating_object.getFloating(), floating_test_case);
    EXPECT_EQ(floating_object.getType(), ObjectType::Number);
    EXPECT_EQ(floating_object.getNumberType(), NumberType::Floating);
    EXPECT_EQ(floating_object.info(), ss.str());
    EXPECT_TRUE(floating_object.isComparable());
    {
        std::unique_ptr<NumberObject> cloned(dynamic_cast<NumberObject*>(integer_object.clone()));
        EXPECT_EQ(integer_object.getType(), cloned->getType());
        EXPECT_EQ(integer_object.getInteger(), cloned->getInteger());
    }

    {
        std::unique_ptr<NumberObject> cloned(dynamic_cast<NumberObject*>(floating_object.clone()));
        EXPECT_EQ(floating_object.getType(), cloned->getType());
        EXPECT_EQ(floating_object.getFloating(), cloned->getFloating());
    }
}

TEST(NumberTypeTest, testNumberCompare)
{
    {
        // NUMBER WITH SOMETHING ELSE
        StringObject string("dummy");
        NumberObject number(2);
        EXPECT_THROW(number.compare(string), TypeSystemError);
    }
    {
        // BOTH INTEGER
        NumberObject low(1);
        NumberObject low2(1);
        NumberObject middle(2);
        EXPECT_EQ(low.compare(low2), 0);
        EXPECT_EQ(low.compare(middle), -1);
        EXPECT_EQ(middle.compare(low), 1);
    }
    {
        // BOTH FLOAT
        NumberObject low(2.71f);
        NumberObject low2(2.71f);
        NumberObject middle(3.14f);
        EXPECT_EQ(low.compare(low2), 0);
        EXPECT_EQ(low.compare(middle), -1);
        EXPECT_EQ(middle.compare(low), 1);
    }
    {
        // INT WITH FLOAT
        NumberObject low(2);
        NumberObject low2(2.0f);
        NumberObject middle(3.14f);
        EXPECT_EQ(low.compare(low2), 0);
        EXPECT_EQ(low.compare(middle), -1);
        EXPECT_EQ(middle.compare(low), 1);
    }
    {
        // FLOAT WITH INT
        NumberObject low(2.0f);
        NumberObject low2(2);
        NumberObject middle(3);
        EXPECT_EQ(low.compare(low2), 0);
        EXPECT_EQ(low.compare(middle), -1);
        EXPECT_EQ(middle.compare(low), 1);
    }
}

TEST(NumberTypeTest, testAssignment)
{
    NumberObject obj1(1);
    NumberObject obj2(2);
    obj1 = obj2;
    EXPECT_EQ(obj1.info(), obj2.info());
    NumberObject obj3(1.3f);
    NumberObject obj4(2.4f);
    obj3 = obj4;
    EXPECT_EQ(obj3.info(), obj4.info());
    obj2 = obj1;
    obj3 = std::move(obj1);
    EXPECT_EQ(obj3.info(), obj2.info());
    obj3 = obj4;
    obj1 = std::move(obj3);
    EXPECT_EQ(obj1.info(), obj3.info());
}

TEST(NumberTypeTest, testMoveCtor)
{
    NumberObject obj1(1);
    NumberObject obj2(std::move(obj1));
    EXPECT_EQ(obj2.info(), "Integer => 1");
    NumberObject obj3(1.2f);
    auto obj4 = obj3;
    NumberObject obj5(std::move(obj4));
    EXPECT_EQ(obj5.info(), obj3.info());
}

}  // namespace nastya::typesystem
