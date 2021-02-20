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

TEST(ComplexTokenizerTest, testEmptyExpressions)
{
    std::vector test_cases = {"()", "( )", "  (  )  "};

    std::vector expected_tokens = {Token{TokenType::S_expr_begin}, Token{TokenType::S_expr_end}, Token{TokenType::Eof}};
    for (auto test_case : test_cases)
    {
        Tokenizer parser(test_case);
        for (auto expected_token : expected_tokens)
        {
            EXPECT_EQ(parser.getToken(), expected_token);
        }
    }
}

TEST(ComplexTokenizerTest, testComplexExpression)
{
    Tokenizer parser("(check_if (define lambda name) #true \"expected_string\")");
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

}
