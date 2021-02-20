//
// Created by caedus on 20.02.2021.
//

#include "Tokenizer/TokenizerException.hpp"
#include "Tokenizer/Tokenizer.hpp"
#include "Common.hpp"

#include <vector>

#include <gtest/gtest.h>

namespace nastya::tokens {
using namespace ::testing;

TEST(ReservedCharacterTokenTest, testKeywordCharacter)
{
    using StringTestCase = TestCase<std::string, Token>;
    std::vector test_cases = {
        StringTestCase{std::string("("), Token{TokenType::S_expr_begin}},
        StringTestCase{std::string(")"), Token{TokenType::S_expr_end}},
        StringTestCase{std::string("'"), Token{TokenType::Quote}},
        StringTestCase{std::string(""), Token{TokenType::Eof}},
        StringTestCase{std::string("+"), Token{TokenType::Label, std::string("+")}},
        StringTestCase{std::string("-"), Token{TokenType::Label, std::string("-")}},
        StringTestCase{std::string("*"), Token{TokenType::Label, std::string("*")}},
        StringTestCase{std::string("/"), Token{TokenType::Label, std::string("/")}},
        StringTestCase{std::string("^"), Token{TokenType::Label, std::string("^")}},
        StringTestCase{std::string("%"), Token{TokenType::Label, std::string("%")}}
    };
    for (const auto& test_case: test_cases) {
        Tokenizer tokenizer(test_case.first);
        EXPECT_EQ(tokenizer.getToken(), test_case.second);
    }
}

}
