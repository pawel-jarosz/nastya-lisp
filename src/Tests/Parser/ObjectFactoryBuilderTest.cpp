#include <gtest/gtest.h>

#include "Parser/ObjectFactory.hpp"
#include "Parser/ObjectFactoryBuilder.hpp"
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
    tokens::Token t{tokens::TokenType::Boolean, false};
    std::unique_ptr<typesystem::IObject> object{factory.create(t)};
    EXPECT_EQ(object->getType(), typesystem::ObjectType::Boolean);
    auto boolean_object = dynamic_cast<typesystem::BooleanObject*>(object.get());
    EXPECT_EQ(boolean_object->getValue(), (std::get<bool>(t.value)));
}

TEST_F(ObjectFactoryBuilderTest, testCreateInteger)
{
    tokens::Token t{tokens::TokenType::Integer, 123};
    std::unique_ptr<typesystem::IObject> object{factory.create(t)};
    EXPECT_EQ(object->getType(), typesystem::ObjectType::Number);
    auto number_object = dynamic_cast<typesystem::NumberObject*>(object.get());
    EXPECT_EQ(number_object->getNumberType(), typesystem::NumberType::Integer);
    EXPECT_EQ(number_object->getInteger(), (std::get<int>(t.value)));
}

TEST_F(ObjectFactoryBuilderTest, testCreateFloat)
{
    tokens::Token t{tokens::TokenType::Floating, 123.123f};
    std::unique_ptr<typesystem::IObject> object{factory.create(t)};
    EXPECT_EQ(object->getType(), typesystem::ObjectType::Number);
    auto number_object = dynamic_cast<typesystem::NumberObject*>(object.get());
    EXPECT_EQ(number_object->getNumberType(), typesystem::NumberType::Floating);
    EXPECT_EQ(number_object->getFloating(), (std::get<float>(t.value)));
}

TEST_F(ObjectFactoryBuilderTest, testCreateString)
{
    tokens::Token t{tokens::TokenType::String, std::string("123.123f")};
    std::unique_ptr<typesystem::IObject> object{factory.create(t)};
    EXPECT_EQ(object->getType(), typesystem::ObjectType::String);
    auto string_object = dynamic_cast<typesystem::StringObject*>(object.get());
    EXPECT_EQ(string_object->getValue(), (std::get<std::string>(t.value)));
}

TEST_F(ObjectFactoryBuilderTest, testCreateLabel)
{
    tokens::Token t{tokens::TokenType::Label, std::string("label")};
    std::unique_ptr<typesystem::IObject> object{factory.create(t)};
    EXPECT_EQ(object->getType(), typesystem::ObjectType::Label);
    auto label_object = dynamic_cast<typesystem::LabelObject*>(object.get());
    EXPECT_EQ(label_object->getValue(), (std::get<std::string>(t.value)));
}

}  // namespace nastya::lisp
