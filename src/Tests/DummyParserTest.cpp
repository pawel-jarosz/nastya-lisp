//
// Created by caedus on 03.12.2020.
//

#include <gtest/gtest.h>

#include "Parser/DummyParser.hpp"
#include "Parser/ParserException.hpp"

using namespace nastya::parser;

namespace {

Token create_boolean_token(bool value)
{
    return Token{TokenType::Boolean, value};
}

Token create_integer_token(int value)
{
    return Token{TokenType::Integer, value};
}

Token create_floating_token(float value)
{
    return Token{TokenType::Floating, value};
}

Token create_string_token(std::string value)
{
    std::stringstream ss;
    for (const auto& ch : value)
    {
        if (ch == '\"')
        {
            ss << "\\\"";
            continue;
        }
        ss << ch;
    }
    return Token{TokenType::String, ss.str()};
}

Token create_label_token(std::string value)
{
    return Token{TokenType::Label, value};
}

template <typename GivenValue, typename ExpectedValue>
struct TestCase
{
    GivenValue first;
    ExpectedValue second;
};

}  // namespace

TEST(DummyParserTest, testKeywordCharacter)
{
    {
        DummyParser parser{"("};
        EXPECT_EQ(parser.getToken(), Token{TokenType::S_expr_begin});
    }
    {
        DummyParser parser{")"};
        EXPECT_EQ(parser.getToken(), Token{TokenType::S_expr_end});
    }
    {
        DummyParser parser{"'"};
        EXPECT_EQ(parser.getToken(), Token{TokenType::Quote});
    }
    {
        DummyParser parser{""};
        EXPECT_EQ(parser.getToken(), Token{TokenType::Eof});
    }
}

TEST(DummyParserTest, testInteger)
{
    using IntegerTestCase = TestCase<std::string, int>;
    std::vector positive_cases = {
        IntegerTestCase{"123", 123},
        IntegerTestCase{"-123", -123},
        IntegerTestCase{"       123", 123},
        IntegerTestCase{"   \t  123    \t", 123},
        IntegerTestCase{"123\t\t", 123},
        IntegerTestCase{"  \t-123", -123},
        IntegerTestCase{"  \t-123  \t\t   ", -123},
        IntegerTestCase{"-123  \t\t   ", -123},
    };
    for (const auto& test_case : positive_cases)
    {
        DummyParser parser(test_case.first);
        EXPECT_EQ(parser.getToken(), create_integer_token(test_case.second));
    }

    // TODO: verify negative cases
}

TEST(DummyParserTest, testFloating)
{
    using FloatingTestCase = TestCase<std::string, float>;
    std::vector test_cases = {FloatingTestCase{"123.456", 123.456},
                              FloatingTestCase{"-123.456", -123.456},
                              FloatingTestCase{"123.456e10", 123.456e10},
                              FloatingTestCase{"123.456e-2", 123.456e-2},
                              FloatingTestCase{"123.456f", 123.456},
                              FloatingTestCase{"123.456d", 123.456}};

    for (const auto& test_case : test_cases)
    {
        DummyParser parser(test_case.first);
        EXPECT_EQ(parser.getToken(), create_floating_token(test_case.second));
    }
    FloatingTestCase invalid_test{"123.456u", 123.456};
    DummyParser parser(invalid_test.first);
    EXPECT_THROW(parser.getToken(), ParserException);
}

TEST(DummyParserTest, testBoolean)
{
    {
        DummyParser parser{"#true"};
        EXPECT_EQ(parser.getToken(), (Token{TokenType::Boolean, true}));
    }
    {
        DummyParser parser{"#false"};
        EXPECT_EQ(parser.getToken(), (Token{TokenType::Boolean, false}));
    }
}

TEST(DummyParserTest, testLabel)
{
    using LabelTestCase = TestCase<std::string, std::string>;
    std::vector test_cases = {LabelTestCase{"dummy", "dummy"}};
    for (const auto& test_case : test_cases)
    {
        DummyParser parser(test_case.first);
        std::cout << "Test string: " << test_case.first << std::endl;
        EXPECT_EQ(parser.getToken(), create_label_token(test_case.second));
    }
    // TODO: Verify negative case
}

TEST(DummyParserTest, testString)
{
    using StringTestCase = TestCase<std::string, std::string>;
    std::vector test_cases = {
        StringTestCase{"\"dummy\"", "dummy"},
        StringTestCase{"\"more than one word\"", "more than one word"},
        // TODO: fix escaped double quote
        // StringTestCase{"\"test case has \\\" character inside\"",
        //               "test case has \\\" character inside"},
        StringTestCase{"\"string has blank characters inside \n\t\"", "string has blank characters inside \n\t"}};
    for (const auto& test_case : test_cases)
    {
        DummyParser parser(test_case.first);
        std::cout << "Test string: " << test_case.first << std::endl;
        EXPECT_EQ(parser.getToken(), create_string_token(test_case.second));
    }
}

TEST(DummyParserTest, testEmptyExpressions)
{
    std::vector test_cases = {"()", "( )", "  (  )  "};

    std::vector expected_tokens = {Token{TokenType::S_expr_begin}, Token{TokenType::S_expr_end}, Token{TokenType::Eof}};
    for (auto test_case : test_cases)
    {
        DummyParser parser(test_case);
        for (auto expected_token : expected_tokens)
        {
            EXPECT_EQ(parser.getToken(), expected_token);
        }
    }
}

TEST(DummyParserTest, testComplexExpression)
{
    DummyParser parser("(check_if (define lambda name) #true \"expected_string\")");
    std::vector expected_tokens = {Token{TokenType::S_expr_begin},
                                   create_label_token("check_if"),
                                   Token{TokenType::S_expr_begin},
                                   create_label_token("define"),
                                   create_label_token("lambda"),
                                   create_label_token("name"),
                                   Token{TokenType::S_expr_end},
                                   create_boolean_token(true),
                                   create_string_token("expected_string"),
                                   Token{TokenType::S_expr_end},
                                   Token{TokenType::Eof}};

    for (const auto expected_token : expected_tokens)
    {
        const auto received_token = parser.getToken();
        std::cout << "Expected token: " << expected_token << std::endl;
        std::cout << "Received token: " << received_token << std::endl;
        EXPECT_EQ(received_token, expected_token);
    }
}

TEST(DummyParserTest, testTokenTypeStream) {
    {
        std::stringstream ss;
        ss << TokenType::Boolean;
        EXPECT_EQ(ss.str(), "Boolean");
    }
    {
        std::stringstream ss;
        ss << TokenType::Integer;
        EXPECT_EQ(ss.str(), "Integer");
    }
    {
        std::stringstream ss;
        ss << TokenType::Floating;
        EXPECT_EQ(ss.str(), "Floating");
    }
    {
        std::stringstream ss;
        ss << TokenType::String;
        EXPECT_EQ(ss.str(), "String");
    }
    {
        std::stringstream ss;
        ss << TokenType::Label;
        EXPECT_EQ(ss.str(), "Label");
    }
    {
        std::stringstream ss;
        ss << TokenType::S_expr_begin;
        EXPECT_EQ(ss.str(), "S_expr_begin");
    }
    {
        std::stringstream ss;
        ss << TokenType::S_expr_end;
        EXPECT_EQ(ss.str(), "S_expr_end");
    }
    {
        std::stringstream ss;
        ss << TokenType::Quote;
        EXPECT_EQ(ss.str(), "Quote");
    }
    {
        std::stringstream ss;
        ss << TokenType::Eof;
        EXPECT_EQ(ss.str(), "Eof");
    }
}

TEST(DummyParserTest, testCompareToken) {
    Token a{TokenType::Eof};
    Token b{TokenType::S_expr_end};
    EXPECT_FALSE(a == b);
}

TEST(DummyParserTest, testNotTerminatedQuotationMark) {
    const std::string test_case = "\"not terminated quotation";
    DummyParser parser(test_case);
    EXPECT_THROW(parser.getToken(), ParserException);
}
