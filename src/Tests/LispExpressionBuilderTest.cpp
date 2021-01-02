//
// Created by caedus on 15.12.2020.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "LispExpression/LispExpressionBuilder.hpp"
#include "LispExpression/ObjectFactory.hpp"
#include "LispExpression/ObjectFactoryBuilder.hpp"
#include "LispExpression/Testing/ListBuilder.hpp"
#include "LispExpression/TypeSystem/BooleanObject.hpp"
#include "LispExpression/TypeSystem/LabelObject.hpp"
#include "LispExpression/TypeSystem/ListObject.hpp"
#include "LispExpression/TypeSystem/NumberObject.hpp"
#include "LispExpression/TypeSystem/StringObject.hpp"
#include "Parser/DummyParser.hpp"
#include "Parser/Interface/IParser.hpp"

namespace nastya {

using namespace testing;

class ParserMock : public parser::IParser
{
public:
    MOCK_METHOD(parser::Token, getToken, ());
    MOCK_METHOD(bool, isEmpty, ());
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
    parser::Token test_case{parser::TokenType::Floating, 2.3f};
    EXPECT_CALL(parser, getToken()).WillOnce(Return(test_case)).WillOnce(Return(parser::Token{parser::TokenType::Eof}));
    lisp::LispExpressionBuilder expression_builder(parser, object_factory);
    auto result = expression_builder.build();
    EXPECT_EQ(result.getType(), lisp::ObjectType::Number);
    auto number = dynamic_cast<lisp::typesystem::NumberObject&>(result.getRawObject());
    EXPECT_EQ(number.getNumberType(), lisp::NumberType::Floating);
    EXPECT_EQ(number.getFloating(), std::get<float>(test_case.value));
}

TEST_F(LispExpressionBuilderTest, testIntegerNumber)
{
    ParserMock parser;
    parser::Token test_case{parser::TokenType::Integer, 2};
    EXPECT_CALL(parser, getToken()).WillOnce(Return(test_case)).WillOnce(Return(parser::Token{parser::TokenType::Eof}));
    lisp::LispExpressionBuilder expression_builder(parser, object_factory);
    auto result = expression_builder.build();
    EXPECT_EQ(result.getType(), lisp::ObjectType::Number);
    auto number = dynamic_cast<lisp::typesystem::NumberObject&>(result.getRawObject());
    EXPECT_EQ(number.getNumberType(), lisp::NumberType::Integer);
    EXPECT_EQ(number.getInteger(), std::get<int>(test_case.value));
}

TEST_F(LispExpressionBuilderTest, testLabel)
{
    ParserMock parser;
    parser::Token test_case{parser::TokenType::Label, std::string("Label")};
    EXPECT_CALL(parser, getToken()).WillOnce(Return(test_case)).WillOnce(Return(parser::Token{parser::TokenType::Eof}));
    lisp::LispExpressionBuilder expression_builder(parser, object_factory);
    auto result = expression_builder.build();
    EXPECT_EQ(result.getType(), lisp::ObjectType::Label);
    auto label = dynamic_cast<lisp::typesystem::LabelObject&>(result.getRawObject());
    EXPECT_EQ(label.getValue(), std::get<std::string>(test_case.value));
}

TEST_F(LispExpressionBuilderTest, testString)
{
    ParserMock parser;
    parser::Token test_case{parser::TokenType::String, std::string("String")};
    EXPECT_CALL(parser, getToken()).WillOnce(Return(test_case)).WillOnce(Return(parser::Token{parser::TokenType::Eof}));
    lisp::LispExpressionBuilder expression_builder(parser, object_factory);
    auto result = expression_builder.build();
    EXPECT_EQ(result.getType(), lisp::ObjectType::String);
    auto string_object = dynamic_cast<lisp::typesystem::StringObject&>(result.getRawObject());
    EXPECT_EQ(string_object.getValue(), std::get<std::string>(test_case.value));
}

TEST_F(LispExpressionBuilderTest, testBoolean)
{
    ParserMock parser;
    parser::Token test_case{parser::TokenType::Boolean, true};
    EXPECT_CALL(parser, getToken()).WillOnce(Return(test_case)).WillOnce(Return(parser::Token{parser::TokenType::Eof}));
    lisp::LispExpressionBuilder expression_builder(parser, object_factory);
    auto result = expression_builder.build();
    EXPECT_EQ(result.getType(), lisp::ObjectType::Boolean);
    auto boolean = dynamic_cast<lisp::typesystem::BooleanObject&>(result.getRawObject());
    EXPECT_EQ(boolean.getValue(), std::get<bool>(test_case.value));
}

TEST_F(LispExpressionBuilderTest, testEmptyList)
{
    lisp::testing::ListBuilder list_builder;
    auto test_case = list_builder.build();
    parser::DummyParser parser(test_case.toString());
    lisp::LispExpressionBuilder expression_builder(parser, object_factory);
    EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
}

TEST_F(LispExpressionBuilderTest, testSingleton)
{
    {
        lisp::testing::ListBuilder list_builder;
        auto test_case = list_builder.addNumber(2).build();
        parser::DummyParser parser(test_case.toString());
        lisp::LispExpressionBuilder expression_builder(parser, object_factory);
        EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
    }
    {
        lisp::testing::ListBuilder list_builder;
        auto test_case = list_builder.addLabel("Label").build();
        parser::DummyParser parser(test_case.toString());
        lisp::LispExpressionBuilder expression_builder(parser, object_factory);
        EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
    }
    {
        lisp::testing::ListBuilder list_builder;
        auto test_case = list_builder.addString("String").build();
        parser::DummyParser parser(test_case.toString());
        lisp::LispExpressionBuilder expression_builder(parser, object_factory);
        EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
    }
}

TEST_F(LispExpressionBuilderTest, testMultipleElementsOnTheList)
{
    lisp::testing::ListBuilder list_builder;
    auto test_case = list_builder.addLabel("Label").addString("DummyString").addNumber(2).addNumber(2.3f).build();
    parser::DummyParser parser(test_case.toString());
    lisp::LispExpressionBuilder expression_builder(parser, object_factory);
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
    parser::DummyParser parser(test_case.toString());
    lisp::LispExpressionBuilder expression_builder(parser, object_factory);
    EXPECT_EQ(test_case.toString(), expression_builder.build().toString());
}

TEST_F(LispExpressionBuilderTest, testQuotedExpression)
{
    {
        parser::DummyParser parser("'(1 2 3)");
        lisp::LispExpressionBuilder expression_builder(parser, object_factory);
        EXPECT_EQ("(Quote (1 2 3))", expression_builder.build().toString());
    }
    {
        parser::DummyParser parser("(Tail '(1 2 3))");
        lisp::LispExpressionBuilder expression_builder(parser, object_factory);
        EXPECT_EQ("(Tail (Quote (1 2 3)))", expression_builder.build().toString());
    }
}

TEST_F(LispExpressionBuilderTest, testComplexQuotedExpression)
{
    parser::DummyParser parser("(Tail '((1 2 (3)) (4 5 6)))");
    lisp::LispExpressionBuilder expression_builder(parser, object_factory);
    EXPECT_EQ("(Tail (Quote ((1 2 (3)) (4 5 6))))", expression_builder.build().toString());
}

}  // namespace nastya
