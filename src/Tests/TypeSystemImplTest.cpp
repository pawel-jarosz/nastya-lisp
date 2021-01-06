#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "LispExpression/TypeSystem/BooleanObject.hpp"
#include "LispExpression/TypeSystem/LabelObject.hpp"
#include "LispExpression/TypeSystem/ListObject.hpp"
#include "LispExpression/TypeSystem/NumberObject.hpp"
#include "LispExpression/TypeSystem/StringObject.hpp"
#include "LispExpression/Testing/ListBuilder.hpp"

namespace nastya::lisp::typesystem {

TEST(TypeObjectTest, testBooleanObject)
{
    std::vector test_cases = {true, false};
    std::vector result = {"#true", "Boolean => #true", "#false", "Boolean => #false"};
    size_t i = 0;
    for (const auto& test_case : test_cases)
    {
        BooleanObject object(test_case);
        EXPECT_EQ(object.getValue(), test_case);
        EXPECT_EQ(object.getType(), ObjectType::Boolean);
        std::unique_ptr<BooleanObject> cloned(dynamic_cast<BooleanObject*>(object.clone()));
        EXPECT_EQ(object.getType(), cloned->getType());
        EXPECT_EQ(object.getValue(), cloned->getValue());
        EXPECT_EQ(object.toString(), result[i]);
        EXPECT_EQ(object.info(), result[i + 1]);
        i += 2;
    }
}

TEST(TypeObjectTest, testLabelObject)
{
    std::string test_case = "dummy_label";
    LabelObject object(test_case);
    EXPECT_EQ(object.getValue(), test_case);
    EXPECT_EQ(object.getType(), ObjectType::Label);
    EXPECT_EQ(object.info(), "Label => " + test_case);
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
    EXPECT_EQ(object.info(), "String => \"" + test_case + "\"");
    std::unique_ptr<StringObject> cloned(dynamic_cast<StringObject*>(object.clone()));
    EXPECT_EQ(object.getType(), cloned->getType());
    EXPECT_EQ(object.getValue(), cloned->getValue());
}

TEST(TypeObjectTest, testNumberObject)
{
    NumberObject object;
    EXPECT_EQ(object.getInteger(), 0);
    EXPECT_EQ(object.getNumberType(), NumberType::Integer);

    int integer_test_case = 132;
    NumberObject integer_object(integer_test_case);
    EXPECT_EQ(integer_object.getInteger(), integer_test_case);
    EXPECT_EQ(integer_object.getType(), ObjectType::Number);
    EXPECT_EQ(integer_object.getNumberType(), NumberType::Integer);
    EXPECT_EQ(integer_object.info(), "Integer => " + std::to_string(integer_test_case));

    float floating_test_case = 0.12345;
    std::stringstream ss;
    ss << "Floating => " << floating_test_case;
    NumberObject floating_object(floating_test_case);
    EXPECT_EQ(floating_object.getFloating(), floating_test_case);
    EXPECT_EQ(floating_object.getType(), ObjectType::Number);
    EXPECT_EQ(floating_object.getNumberType(), NumberType::Floating);
    EXPECT_EQ(floating_object.info(), ss.str());
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

TEST(TypeObjectType, testAssignment) {
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

TEST(TypeObjectTest, testMoveCtor) {
    NumberObject obj1(1);
    NumberObject obj2(std::move(obj1));
    EXPECT_EQ(obj2.info(), "Integer => 1");
    NumberObject obj3(1.2f);
    auto obj4 = obj3;
    NumberObject obj5(std::move(obj4));
    EXPECT_EQ(obj5.info(), obj3.info());
}

TEST(TypeObjectTest, testList)
{
    ListObject list;
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_EQ(list.toString(), "()");
    EXPECT_EQ(list.info(), "List => ()");
    testing::ListBuilder builder;
    auto arg = builder.addLabel("abc").addString("demo").openList()
        .addNumber(1).addNumber(3).closeList().build();
    auto complex_list = dynamic_cast<ListObject&>(arg.getRawObject());
    EXPECT_EQ(complex_list.getSize(), 3);
    EXPECT_EQ(complex_list.toString(), "(abc \"demo\" (1 3))");
}

}  // namespace nastya::lisp::typesystem
