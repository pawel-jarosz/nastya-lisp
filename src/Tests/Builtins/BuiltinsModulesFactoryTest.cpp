//
// Created by caedus on 23.02.2021.
//

#include "Builtins/BuiltinsModulesFactory.hpp"

#include <gtest/gtest.h>

namespace nastya::builtins {
using namespace ::testing;

struct BuiltinsModulesFactoryTest : Test {
    BuiltinsModulesFactory factory;
};

TEST_F(BuiltinsModulesFactoryTest, testCreateSyntax) {
    const auto syntaxModule = factory.createSyntax();
    EXPECT_EQ(syntaxModule->getModuleName(), "Lang.Syntax");
}

TEST_F(BuiltinsModulesFactoryTest, testCreateCompare) {
    const auto syntaxModule = factory.createCompare();
    EXPECT_EQ(syntaxModule->getModuleName(), "Lang.Compare");
}

TEST_F(BuiltinsModulesFactoryTest, testCreateLists) {
    const auto syntaxModule = factory.createLists();
    EXPECT_EQ(syntaxModule->getModuleName(), "Lang.Lists");
}

TEST_F(BuiltinsModulesFactoryTest, testCreateArithmetic) {
    const auto syntaxModule = factory.createArithmetic();
    EXPECT_EQ(syntaxModule->getModuleName(), "Lang.Arithmetic");
}

}