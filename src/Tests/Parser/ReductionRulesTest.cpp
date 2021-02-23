//
// Created by caedus on 21.02.2021.
//

#include <gtest/gtest.h>

#include "Parser/Internal/ParserImpl.hpp"
#include "Parser/LispExpressionException.hpp"
#include "Parser/ObjectFactory.hpp"
#include "Parser/ObjectFactoryBuilder.hpp"
#include "Tokenizer/Types/Token.hpp"
#include "TypeSystem/ObjectStorageException.hpp"

namespace nastya::parser {

struct ReductionRulesTest : ::testing::Test
{
    ReductionRulesTest()
    {
        ObjectFactoryBuilder builder(object_factory);
        builder.build();
    }
    ObjectFactory object_factory;
};

TEST_F(ReductionRulesTest, testSingleObject)
{
    using namespace tokens;
    ParserImpl parser(object_factory);
    parser.dispatch(Token{TokenType::Boolean, true});
    EXPECT_TRUE(parser.m_stack.empty());
    EXPECT_NO_THROW(parser.build());
}

TEST_F(ReductionRulesTest, testListReduction)
{
    using namespace tokens;
    ParserImpl parser(object_factory);
    parser.dispatch(Token{TokenType::S_expr_begin});
    EXPECT_EQ(parser.m_stack.size(), 1);
    parser.dispatch(Token{TokenType::S_expr_end});
    EXPECT_EQ(parser.m_stack.size(), 0);
    auto result = parser.build();
    EXPECT_EQ(result.getType(), typesystem::ObjectType::List);
}

TEST_F(ReductionRulesTest, testIfErrorWhenBuildNotClosedList)
{
    using namespace tokens;
    ParserImpl parser(object_factory);
    parser.dispatch(Token{TokenType::S_expr_begin});
    EXPECT_EQ(parser.m_stack.size(), 1);
    EXPECT_THROW(parser.build(), typesystem::ObjectStorageException);
}

TEST_F(ReductionRulesTest, testQuoteReduction)
{
    using namespace tokens;
    ParserImpl parser(object_factory);
    parser.dispatch(Token{TokenType::Quote});
    EXPECT_EQ(parser.m_stack.size(), 1);
    EXPECT_EQ(parser.m_stack.top()[0].toString(), "Quote");
    parser.dispatch(Token{TokenType::S_expr_begin});
    EXPECT_EQ(parser.m_stack.size(), 2);
    EXPECT_EQ(parser.m_quotation_stack.size(), 1);
    EXPECT_EQ(parser.m_quotation_stack.top(), 1);
    parser.dispatch(Token{TokenType::Integer, 1});
    parser.dispatch(Token{TokenType::Integer, 2});
    parser.dispatch(Token{TokenType::Integer, 3});
    EXPECT_EQ(parser.m_stack.size(), 2);
    parser.dispatch(Token{TokenType::S_expr_end});
    EXPECT_TRUE(parser.m_stack.empty());
    EXPECT_TRUE(parser.m_quotation_stack.empty());
    auto result = parser.build();
    EXPECT_EQ(result.toString(), "(Quote (1 2 3))");
}

TEST_F(ReductionRulesTest, testCloseNotOpenedList)
{
    using namespace tokens;
    ParserImpl parser(object_factory);
    EXPECT_THROW(parser.dispatch(Token{TokenType::S_expr_end}), LispExpressionException);
}

}  // namespace nastya::parser
