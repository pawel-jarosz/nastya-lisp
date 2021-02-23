//
// Created by caedus on 20.02.2021.
//

#include <vector>

#include <gtest/gtest.h>

#include "Common.hpp"
#include "Tokenizer/Tokenizer.hpp"
#include "Tokenizer/TokenizerException.hpp"

namespace nastya::tokens {
using namespace ::testing;

TEST(AtomicValueTokenizerTest, testInteger)
{
    using IntegerTestCase = TestCase<std::string, int>;
    std::vector positive_cases = {IntegerTestCase{"123", 123}, IntegerTestCase{"-123", -123}};
    for (const auto& test_case : positive_cases)
    {
        Tokenizer parser(test_case.first);
        EXPECT_EQ(parser.getToken(), create_integer_token(test_case.second));
    }
}

TEST(AtomicValueTokenizerTest, testFloating)
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
        Tokenizer parser(test_case.first);
        EXPECT_EQ(parser.getToken(), create_floating_token(test_case.second));
    }
    FloatingTestCase invalid_test{"123.456u", 123.456};
    Tokenizer parser(invalid_test.first);
    EXPECT_THROW(parser.getToken(), TokenizerException);
}

TEST(AtomicValueTokenizerTest, testBoolean)
{
    {
        Tokenizer parser{"#true"};
        EXPECT_EQ(parser.getToken(), (Token{TokenType::Boolean, true}));
    }
    {
        Tokenizer parser{"#false"};
        EXPECT_EQ(parser.getToken(), (Token{TokenType::Boolean, false}));
    }
}

TEST(AtomicValueTokenizerTest, testLabel)
{
    using LabelTestCase = TestCase<std::string, std::string>;
    std::vector test_cases = {LabelTestCase{"dummy", "dummy"}};
    for (const auto& test_case : test_cases)
    {
        Tokenizer parser(test_case.first);
        std::cout << "Test string: " << test_case.first << std::endl;
        EXPECT_EQ(parser.getToken(), create_label_token(test_case.second));
    }
    std::vector<std::string> negative_testcases{"#dummy_label"
                                                "expected-error"};
    for (const auto& test_case : negative_testcases)
    {
        Tokenizer parser(test_case);
        EXPECT_THROW(parser.getToken(), TokenizerException);
    }
}

}  // namespace nastya::tokens
