#include <gtest/gtest.h>

#include "LispExpression/ObjectFactory.hpp"
#include "LispExpression/ObjectFactoryBuilder.hpp"
#include "TypeSystem/Types/BooleanObject.hpp"
#include "TypeSystem/Types/LabelObject.hpp"
#include "TypeSystem/Types/NumberObject.hpp"
#include "TypeSystem/Types/StringObject.hpp"

namespace nastya::lisp {

struct ObjectFactoryBuilderTest : public ::testing::Test
{
    ObjectFactoryBuilderTest()
    {
        ObjectFactoryBuilder builder(factory);
        builder.build();
    }
    ObjectFactory factory;
};

TEST_F(ObjectFactoryBuilderTest, testCreateBoolean)
{
    parser::Token t{parser::TokenType::Boolean, false};
    std::unique_ptr<IObject> object{factory.create(t)};
    EXPECT_EQ(object->getType(), ObjectType::Boolean);
    auto boolean_object = dynamic_cast<typesystem::BooleanObject*>(object.get());
    EXPECT_EQ(boolean_object->getValue(), (std::get<bool>(t.value)));
}

TEST_F(ObjectFactoryBuilderTest, testCreateInteger)
{
    parser::Token t{parser::TokenType::Integer, 123};
    std::unique_ptr<IObject> object{factory.create(t)};
    EXPECT_EQ(object->getType(), ObjectType::Number);
    auto number_object = dynamic_cast<typesystem::NumberObject*>(object.get());
    EXPECT_EQ(number_object->getNumberType(), NumberType::Integer);
    EXPECT_EQ(number_object->getInteger(), (std::get<int>(t.value)));
}

TEST_F(ObjectFactoryBuilderTest, testCreateFloat)
{
    parser::Token t{parser::TokenType::Floating, 123.123f};
    std::unique_ptr<IObject> object{factory.create(t)};
    EXPECT_EQ(object->getType(), ObjectType::Number);
    auto number_object = dynamic_cast<typesystem::NumberObject*>(object.get());
    EXPECT_EQ(number_object->getNumberType(), NumberType::Floating);
    EXPECT_EQ(number_object->getFloating(), (std::get<float>(t.value)));
}

TEST_F(ObjectFactoryBuilderTest, testCreateString)
{
    parser::Token t{parser::TokenType::String, std::string("123.123f")};
    std::unique_ptr<IObject> object{factory.create(t)};
    EXPECT_EQ(object->getType(), ObjectType::String);
    auto string_object = dynamic_cast<typesystem::StringObject*>(object.get());
    EXPECT_EQ(string_object->getValue(), (std::get<std::string>(t.value)));
}

TEST_F(ObjectFactoryBuilderTest, testCreateLabel)
{
    parser::Token t{parser::TokenType::Label, std::string("label")};
    std::unique_ptr<IObject> object{factory.create(t)};
    EXPECT_EQ(object->getType(), ObjectType::Label);
    auto label_object = dynamic_cast<typesystem::LabelObject*>(object.get());
    EXPECT_EQ(label_object->getValue(), (std::get<std::string>(t.value)));
}

}  // namespace nastya::lisp
