//
// Created by caedus on 20.02.2021.
//

#include <gtest/gtest.h>

#include "Tokenizer/Types/Token.hpp"

namespace nastya::tokens {

TEST(TokenImplTest, testBooleanStreams)
{
    {
        std::stringstream ss;
        ss << TokenType::Boolean;
        EXPECT_EQ(ss.str(), "Boolean");
    }
    {
        std::stringstream ss;
        Token t{TokenType::Boolean, false};
        ss << t;
        EXPECT_EQ(ss.str(), "Token Boolean => False");
    }
    {
        std::stringstream ss;
        Token t{TokenType::Boolean, true};
        ss << t;
        EXPECT_EQ(ss.str(), "Token Boolean => True");
    }
}

TEST(TokenImplTest, testIntegerStream)
{
    {
        std::stringstream ss;
        ss << TokenType::Integer;
        EXPECT_EQ(ss.str(), "Integer");
    }
    {
        std::stringstream ss;
        Token t{TokenType::Integer, 2};
        ss << t;
        EXPECT_EQ(ss.str(), "Token Integer => 2");
    }
}

TEST(TokenImplTest, testFloatingStream)
{
    {
        std::stringstream ss;
        ss << TokenType::Floating;
        EXPECT_EQ(ss.str(), "Floating");
    }
    {
        std::stringstream ss;
        Token t{TokenType::Floating, 2.3f};
        ss << t;
        EXPECT_EQ(ss.str(), "Token Floating => 2.3");
    }
}

TEST(TokenImplTest, testStringStream)
{
    {
        std::stringstream ss;
        ss << TokenType::String;
        EXPECT_EQ(ss.str(), "String");
    }
    {
        std::stringstream ss;
        Token t{TokenType::String, std::string("dummy string")};
        ss << t;
        EXPECT_EQ(ss.str(), "Token String => dummy string");
    }
}

TEST(TokenImplTest, testLabelStream)
{
    {
        std::stringstream ss;
        ss << TokenType::Label;
        EXPECT_EQ(ss.str(), "Label");
    }
    {
        std::stringstream ss;
        Token t{TokenType::Label, std::string("dummy_label")};
        ss << t;
        EXPECT_EQ(ss.str(), "Token Label => dummy_label");
    }
}

TEST(TokenImplTest, testNoValueStream)
{
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

TEST(TokenImplTest, testCompareToken)
{
    {
        Token a{TokenType::Eof};
        Token b{TokenType::S_expr_end};
        EXPECT_FALSE(a == b);
    }
    {
        Token a{TokenType::Integer, 2};
        Token b{TokenType::Integer, 2};
        EXPECT_TRUE(a == b);
    }
}

}  // namespace nastya::tokens
