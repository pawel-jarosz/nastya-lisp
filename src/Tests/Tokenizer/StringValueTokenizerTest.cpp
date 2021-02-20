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

TEST(StringValueTokenizerTest, testString)
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
        Tokenizer parser(test_case.first);
        std::cout << "Test string: " << test_case.first << std::endl;
        EXPECT_EQ(parser.getToken(), create_string_token(test_case.second));
    }
}

TEST(StringValueTokenizerTest, testNotTerminatedQuotationMark) {
    const std::string test_case = "\"not terminated quotation";
    Tokenizer parser(test_case);
    EXPECT_THROW(parser.getToken(), TokenizerException);
}

}
