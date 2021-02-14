//
// Created by caedus on 15.12.2020.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Parser/ObjectFactory.hpp"
#include "Parser/ObjectFactoryBuilder.hpp"
#include "Parser/Parser.hpp"
#include "Parser/Testing/ListBuilder.hpp"
#include "Tokenizer/Interface/ITokenizer.hpp"
#include "Tokenizer/Tokenizer.hpp"
#include "TypeSystem/Types/BooleanObject.hpp"
#include "TypeSystem/Types/LabelObject.hpp"
#include "TypeSystem/Types/ListObject.hpp"
#include "TypeSystem/Types/NumberObject.hpp"
#include "TypeSystem/Types/StringObject.hpp"

namespace nastya {

using namespace testing;

class ParserMock : public tokens::ITokenizer
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
        lisp::ObjectFactoryBuilder builder(object_factory);
        builder.build();
    }
    lisp::ObjectFactory object_factory;
};

TEST_F(LispExpressionBuilderTest, testFloatingNumber)
{
    ParserMock parser;
    tokens::Token test_case{tokens::TokenType::Floating, 2.3f};
    EXPECT_CALL(parser, getToken()).WillOnce(Return(test_case)).WillOnce(Return(tokens::Token{tokens::TokenType::Eof}));
    lisp::Parser expression_builder(parser, object_factory);
    auto result = expression_builder.build();
    EXPECT_EQ(result.getType(), typesystem::ObjectType::Number);
    auto number = dynamic_cast<typesystem::NumberObject&>(result.getRawObject());
    EXPECT_EQ(number.getNumberType(), typesystem::NumberType::Floating);
    EXPECT_EQ(number.getFloating(), std::get<float>(test_case.value));
}

TEST_F(LispExpressionBuilderTest, testIntegerNumber)
{
    ParserMock parser;
    tokens::Token test_case{tokens::TokenType::Integer, 2};
    EXPECT_CALL(parser, getToken()).WillOnce(Return(test_case)).WillOnce(Return(tokens::Token{tokens::TokenType::Eof}));
    lisp::Parser expression_builder(parser, object_factory);
    auto result = expression_builder.build();
    EXPECT_EQ(result.getType(), typesystem::ObjectType::Number);
    auto number = dynamic_cast<typesystem::NumberObject&>(result.getRawObject());
    EXPECT_EQ(number.getNumberType(), typesystem::NumberType::Integer);
    EXPECT_EQ(number.getInteger(), std::get<int>(test_case.value));
}

TEST_F(LispExpressionBuilderTest, testLabel)
{
    ParserMock parser;
    tokens::Token test_case{tokens::TokenType::Label, std::string("Label")};
    EXPECT_CALL(parser, getToken()).WillOnce(Return(test_case)).WillOnce(Return(tokens::Token{tokens::TokenType::Eof}));
    lisp::Parser expression_builder(parser, object_factory);
    auto result = expression_builder.build();
    EXPECT_EQ(result.getType(), typesystem::ObjectType::Label);
    auto label = dynamic_cast<typesystem::LabelObject&>(result.getRawObject());
    EXPECT_EQ(label.getValue(), std::get<std::string>(test_case.value));
}

TEST_F(LispExpressionBuilderTest, testString)
{
    ParserMock parser;
    tokens::Token test_case{tokens::TokenType::String, std::string("String")};
    EXPECT_CALL(parser, getToken()).WillOnce(Return(test_case)).WillOnce(Return(tokens::Token{tokens::TokenType::Eof}));
    lisp::Parser expression_builder(parser, object_factory);
    auto result = expression_builder.build();
    EXPECT_EQ(result.getType(), typesystem::ObjectType::String);
    auto string_object = dynamic_cast<typesystem::StringObject&>(result.getRawObject());
    EXPECT_EQ(string_object.getValue(), std::get<std::string>(test_case.value));
}

TEST_F(LispExpressionBuilderTest, testBoolean)
{
    ParserMock parser;
    tokens::Token test_case{tokens::TokenType::Boolean, true};
    EXPECT_CALL(parser, getToken()).WillOnce(Return(test_case)).WillOnce(Return(tokens::Token{tokens::TokenType::Eof}));
    lisp::Parser expression_builder(parser, object_factory);
    auto result = expression_builder.build();
    EXPECT_EQ(result.getType(), typesystem::ObjectType::Boolean);
    auto boolean = dynamic_cast<typesystem::BooleanObject&>(result.getRawObject());
    EXPECT_EQ(boolean.getValue(), std::get<bool>(test_case.value));
}

TEST_F(LispExpressionBuilderTest, testEmptyList)
{
    lisp::testing::ListBuilder list_builder;
    auto test_case = list_builder.build();
    tokens::Tokenizer parser(test_case.toString());
    lisp::Parser expression_builder(parser, object_factory);
    EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
}

TEST_F(LispExpressionBuilderTest, testSingleton)
{
    {
        lisp::testing::ListBuilder list_builder;
        auto test_case = list_builder.addNumber(2).build();
        tokens::Tokenizer parser(test_case.toString());
        lisp::Parser expression_builder(parser, object_factory);
        EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
    }
    {
        lisp::testing::ListBuilder list_builder;
        auto test_case = list_builder.addLabel("Label").build();
        tokens::Tokenizer parser(test_case.toString());
        lisp::Parser expression_builder(parser, object_factory);
        EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
    }
    {
        lisp::testing::ListBuilder list_builder;
        auto test_case = list_builder.addString("String").build();
        tokens::Tokenizer parser(test_case.toString());
        lisp::Parser expression_builder(parser, object_factory);
        EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
    }
}

TEST_F(LispExpressionBuilderTest, testMultipleElementsOnTheList)
{
    lisp::testing::ListBuilder list_builder;
    auto test_case = list_builder.addLabel("Label").addString("DummyString").addNumber(2).addNumber(2.3f).build();
    tokens::Tokenizer parser(test_case.toString());
    lisp::Parser expression_builder(parser, object_factory);
    EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
}

TEST_F(LispExpressionBuilderTest, testExpressionWithComplexList)
{
    lisp::testing::ListBuilder list_builder;
    auto test_case = list_builder.addLabel("Label")
                         .openList()
                         .addLabel("Dummy")
                         .addNumber(2)
                         .addNumber(2.3f)
                         .closeList()
                         .addLabel("Next")
                         .build();
    tokens::Tokenizer parser(test_case.toString());
    lisp::Parser expression_builder(parser, object_factory);
    EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
}

TEST_F(LispExpressionBuilderTest, testQuotedExpression)
{
    {
        tokens::Tokenizer parser("'(1 2 3)");
        lisp::Parser expression_builder(parser, object_factory);
        EXPECT_EQ("(Quote (1 2 3))", expression_builder.build().toString());
    }
    {
        tokens::Tokenizer parser("(Tail '(1 2 3))");
        lisp::Parser expression_builder(parser, object_factory);
        EXPECT_EQ("(Tail (Quote (1 2 3)))", expression_builder.build().toString());
    }
}

TEST_F(LispExpressionBuilderTest, testComplexQuotedExpression)
{
    tokens::Tokenizer parser("(Tail '((1 2 (3)) (4 5 6)))");
    lisp::Parser expression_builder(parser, object_factory);
    EXPECT_EQ("(Tail (Quote ((1 2 (3)) (4 5 6))))", expression_builder.build().toString());
}

}  // namespace nastya
