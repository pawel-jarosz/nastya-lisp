//
// Created by caedus on 03.12.2020.
//

#include <gtest/gtest.h>

#include "ParserException.hpp"
#include "DummyParser.hpp"

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
        StringTestCase{"\"string has blank characters inside \n\t\"",
                       "string has blank characters inside \n\t"}};
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

    std::vector expected_tokens = {Token{TokenType::S_expr_begin},
                                   Token{TokenType::S_expr_end},
                                   Token{TokenType::Eof}};
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
    DummyParser parser(
        "(check_if (define lambda name) #true \"expected_string\")");
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
