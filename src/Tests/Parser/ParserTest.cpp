//
// Created by caedus on 23.02.2021.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Parser/ObjectFactory.hpp"
#include "Parser/ObjectFactoryBuilder.hpp"
#include "Parser/Parser.hpp"
#include "Tokenizer/Interface/ITokenizer.hpp"
#include "Tokenizer/Tokenizer.hpp"
#include "TypeSystem/Types/BooleanObject.hpp"
#include "TypeSystem/Types/LabelObject.hpp"
#include "TypeSystem/Types/ListObject.hpp"
#include "TypeSystem/Types/NumberObject.hpp"
#include "TypeSystem/Types/StringObject.hpp"
#include "Utilities/ListBuilder.hpp"

namespace nastya::parser {

using namespace testing;

class TokenizerMock : public tokens::ITokenizer
{
public:
    MOCK_METHOD(tokens::Token, getToken, ());
    MOCK_METHOD(bool, isEmpty, ());
    MOCK_METHOD(void, reset, (std::string));
};

struct LispExpressionBuilderTest : ::testing::Test
{
    LispExpressionBuilderTest()
    {
        ObjectFactoryBuilder builder(object_factory);
        builder.build();
    }
    ObjectFactory object_factory;
};

TEST_F(LispExpressionBuilderTest, testFloatingNumber)
{
    TokenizerMock tokenizer;
    tokens::Token test_case{tokens::TokenType::Floating, 2.3f};
    EXPECT_CALL(tokenizer, getToken()).WillOnce(Return(test_case)).WillOnce(Return(tokens::Token{tokens::TokenType::Eof}));
    Parser expression_builder(tokenizer, object_factory);
    auto result = expression_builder.build();
    EXPECT_EQ(result.getType(), typesystem::ObjectType::Number);
    auto number = dynamic_cast<typesystem::NumberObject&>(result.getRawObject());
    EXPECT_EQ(number.getNumberType(), typesystem::NumberType::Floating);
    EXPECT_EQ(number.getFloating(), std::get<float>(test_case.value));
}

TEST_F(LispExpressionBuilderTest, testIntegerNumber)
{
    TokenizerMock tokenizer;
    tokens::Token test_case{tokens::TokenType::Integer, 2};
    EXPECT_CALL(tokenizer, getToken()).WillOnce(Return(test_case)).WillOnce(Return(tokens::Token{tokens::TokenType::Eof}));
    Parser expression_builder(tokenizer, object_factory);
    auto result = expression_builder.build();
    EXPECT_EQ(result.getType(), typesystem::ObjectType::Number);
    auto number = dynamic_cast<typesystem::NumberObject&>(result.getRawObject());
    EXPECT_EQ(number.getNumberType(), typesystem::NumberType::Integer);
    EXPECT_EQ(number.getInteger(), std::get<int>(test_case.value));
}

TEST_F(LispExpressionBuilderTest, testLabel)
{
    TokenizerMock tokenizer;
    tokens::Token test_case{tokens::TokenType::Label, std::string("Label")};
    EXPECT_CALL(tokenizer, getToken()).WillOnce(Return(test_case)).WillOnce(Return(tokens::Token{tokens::TokenType::Eof}));
    Parser expression_builder(tokenizer, object_factory);
    auto result = expression_builder.build();
    EXPECT_EQ(result.getType(), typesystem::ObjectType::Label);
    auto label = dynamic_cast<typesystem::LabelObject&>(result.getRawObject());
    EXPECT_EQ(label.getValue(), std::get<std::string>(test_case.value));
}

TEST_F(LispExpressionBuilderTest, testString)
{
    TokenizerMock tokenizer;
    tokens::Token test_case{tokens::TokenType::String, std::string("String")};
    EXPECT_CALL(tokenizer, getToken()).WillOnce(Return(test_case)).WillOnce(Return(tokens::Token{tokens::TokenType::Eof}));
    Parser expression_builder(tokenizer, object_factory);
    auto result = expression_builder.build();
    EXPECT_EQ(result.getType(), typesystem::ObjectType::String);
    auto string_object = dynamic_cast<typesystem::StringObject&>(result.getRawObject());
    EXPECT_EQ(string_object.getValue(), std::get<std::string>(test_case.value));
}

TEST_F(LispExpressionBuilderTest, testBoolean)
{
    TokenizerMock tokenizer;
    tokens::Token test_case{tokens::TokenType::Boolean, true};
    EXPECT_CALL(tokenizer, getToken()).WillOnce(Return(test_case)).WillOnce(Return(tokens::Token{tokens::TokenType::Eof}));
    Parser expression_builder(tokenizer, object_factory);
    auto result = expression_builder.build();
    EXPECT_EQ(result.getType(), typesystem::ObjectType::Boolean);
    auto boolean = dynamic_cast<typesystem::BooleanObject&>(result.getRawObject());
    EXPECT_EQ(boolean.getValue(), std::get<bool>(test_case.value));
}

TEST_F(LispExpressionBuilderTest, testEmptyList)
{
    utils::ListBuilder list_builder;
    auto test_case = list_builder.build();
    tokens::Tokenizer tokenizer(test_case.toString());
    Parser expression_builder(tokenizer, object_factory);
    EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
}

TEST_F(LispExpressionBuilderTest, testSingleton)
{
    {
        utils::ListBuilder list_builder;
        auto test_case = list_builder.addNumber(2).build();
        tokens::Tokenizer tokenizer(test_case.toString());
        Parser expression_builder(tokenizer, object_factory);
        EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
    }
    {
        utils::ListBuilder list_builder;
        auto test_case = list_builder.addLabel("Label").build();
        tokens::Tokenizer tokenizer(test_case.toString());
        Parser expression_builder(tokenizer, object_factory);
        EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
    }
    {
        utils::ListBuilder list_builder;
        auto test_case = list_builder.addString("String").build();
        tokens::Tokenizer tokenizer(test_case.toString());
        Parser expression_builder(tokenizer, object_factory);
        EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
    }
}

TEST_F(LispExpressionBuilderTest, testMultipleElementsOnTheList)
{
    utils::ListBuilder list_builder;
    auto test_case = list_builder.addLabel("Label").addString("DummyString").addNumber(2).addNumber(2.3f).build();
    tokens::Tokenizer tokenizer(test_case.toString());
    Parser expression_builder(tokenizer, object_factory);
    EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
}

TEST_F(LispExpressionBuilderTest, testExpressionWithComplexList)
{
    utils::ListBuilder list_builder;
    auto test_case = list_builder.addLabel("Label")
                         .openList()
                         .addLabel("Dummy")
                         .addNumber(2)
                         .addNumber(2.3f)
                         .closeList()
                         .addLabel("Next")
                         .build();
    tokens::Tokenizer tokenizer(test_case.toString());
    Parser expression_builder(tokenizer, object_factory);
    EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
}

TEST_F(LispExpressionBuilderTest, testQuotedExpression)
{
    {
        tokens::Tokenizer tokenizer("'(1 2 3)");
        Parser expression_builder(tokenizer, object_factory);
        EXPECT_EQ("(Quote (1 2 3))", expression_builder.build().toString());
    }
    {
        tokens::Tokenizer tokenizer("(Tail '(1 2 3))");
        Parser expression_builder(tokenizer, object_factory);
        EXPECT_EQ("(Tail (Quote (1 2 3)))", expression_builder.build().toString());
    }
}

TEST_F(LispExpressionBuilderTest, testComplexQuotedExpression)
{
    tokens::Tokenizer tokenizer("(Tail '((1 2 (3)) (4 5 6)))");
    Parser expression_builder(tokenizer, object_factory);
    EXPECT_EQ("(Tail (Quote ((1 2 (3)) (4 5 6))))", expression_builder.build().toString());
}

}  // namespace nastya::parser
