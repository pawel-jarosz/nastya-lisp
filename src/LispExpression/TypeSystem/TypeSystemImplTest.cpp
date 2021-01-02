#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "LispExpression/TypeSystem/BooleanObject.hpp"
#include "LispExpression/TypeSystem/LabelObject.hpp"
#include "LispExpression/TypeSystem/ListObject.hpp"
#include "LispExpression/TypeSystem/NumberObject.hpp"
#include "LispExpression/TypeSystem/StringObject.hpp"

namespace nastya::lisp::typesystem {

TEST(TypeObjectTest, testBooleanObject)
{
    std::vector test_cases = {true, false};
    for (const auto& test_case : test_cases)
    {
        BooleanObject object(test_case);
        EXPECT_EQ(object.getValue(), test_case);
        EXPECT_EQ(object.getType(), ObjectType::Boolean);
        std::unique_ptr<BooleanObject> cloned(dynamic_cast<BooleanObject*>(object.clone()));
        EXPECT_EQ(object.getType(), cloned->getType());
        EXPECT_EQ(object.getValue(), cloned->getValue());
    }
}

TEST(TypeObjectTest, testLabelObject)
{
    std::string test_case = "dummy_label";
    LabelObject object(test_case);
    EXPECT_EQ(object.getValue(), test_case);
    EXPECT_EQ(object.getType(), ObjectType::Label);
    std::unique_ptr<LabelObject> cloned(dynamic_cast<LabelObject*>(object.clone()));
    EXPECT_EQ(object.getType(), cloned->getType());
    EXPECT_EQ(object.getValue(), cloned->getValue());
}

TEST(TypeObjectTest, testStringObject)
{
    std::string test_case = "dummy string";
    StringObject object(test_case);
    EXPECT_EQ(object.getValue(), test_case);
    EXPECT_EQ(object.getType(), ObjectType::String);
    std::unique_ptr<StringObject> cloned(dynamic_cast<StringObject*>(object.clone()));
    EXPECT_EQ(object.getType(), cloned->getType());
    EXPECT_EQ(object.getValue(), cloned->getValue());
}

TEST(TypeObjectTest, testNumberObject)
{
    int integer_test_case = 132;
    NumberObject integer_object(integer_test_case);
    EXPECT_EQ(integer_object.getInteger(), integer_test_case);
    EXPECT_EQ(integer_object.getType(), ObjectType::Number);
    EXPECT_EQ(integer_object.getNumberType(), NumberType::Integer);

    float floating_test_case = 0.5;
    NumberObject floating_object(floating_test_case);
    EXPECT_EQ(floating_object.getFloating(), floating_test_case);
    EXPECT_EQ(floating_object.getType(), ObjectType::Number);
    EXPECT_EQ(floating_object.getNumberType(), NumberType::Floating);

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

TEST(TypeObjectTest, testList)
{
    // TODO: Add test
}

}  // namespace nastya::lisp::typesystem
