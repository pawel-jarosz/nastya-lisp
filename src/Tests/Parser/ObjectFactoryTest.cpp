#include <gtest/gtest.h>
#include "Parser/LispExpressionException.hpp"
#include "Parser/ObjectFactory.hpp"
#include "Tokenizer/Types/Token.hpp"

namespace nastya::lisp {

TEST(ObjectFactoryTest, testObjectFactory)
{
    ObjectFactory factory;
    bool called = false;
    auto callback = [&called](const tokens::Token& p) {
        called = true;
        return nullptr;
    };
    factory.registerToken(tokens::TokenType::String, callback);
    factory.create(tokens::Token{tokens::TokenType::String});
    EXPECT_TRUE(called);
    EXPECT_THROW(factory.create(tokens::Token{tokens::TokenType::S_expr_begin}), lisp::LispExpressionException);
}

}  // namespace nastya::lisp