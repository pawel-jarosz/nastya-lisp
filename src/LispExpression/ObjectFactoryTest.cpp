#include <gtest/gtest.h>

#include "LispExpression/ObjectFactory.hpp"
#include "Parser/Types/Token.hpp"

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
    // TODO: check what if token is not registered
}

}  // namespace nastya::lisp