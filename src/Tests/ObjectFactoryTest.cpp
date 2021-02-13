#include <gtest/gtest.h>
#include "Parser/LispExpressionException.hpp"
#include "Parser/ObjectFactory.hpp"
#include "Tokenizer/Types/Token.hpp"

namespace nastya::lisp {

TEST(ObjectFactoryTest, testObjectFactory)
{
    ObjectFactory factory;
    bool called = false;
    auto callback = [&called](const parser::Token& p) {
        called = true;
        return nullptr;
    };
    factory.registerToken(parser::TokenType::String, callback);
    factory.create(parser::Token{parser::TokenType::String});
    EXPECT_TRUE(called);
    EXPECT_THROW(factory.create(parser::Token{parser::TokenType::S_expr_begin}), lisp::LispExpressionException);
}

}  // namespace nastya::lisp