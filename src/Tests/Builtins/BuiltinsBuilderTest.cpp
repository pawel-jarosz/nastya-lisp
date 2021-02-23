//
// Created by caedus on 23.02.2021.
//

#include "Builtins/BuiltinsBuilder.hpp"
#include "Modules/ModuleRegistry.hpp"
#include "Modules/Module.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace nastya::builtins {
using namespace ::testing;
using namespace modules;

class BuiltinsModulesFactoryMock : public IBuiltinsModuleFactory {
public:
    MOCK_METHOD(std::unique_ptr<IModule>, createSyntax, (), (const, override));
    MOCK_METHOD(std::unique_ptr<IModule>, createLists, (), (const, override));
    MOCK_METHOD(std::unique_ptr<IModule>, createCompare, (), (const, override));
    MOCK_METHOD(std::unique_ptr<IModule>, createArithmetic, (), (const, override));
};

TEST(BuiltinsBuilderTest, testUseOfFactory) {
    BuiltinsModulesFactoryMock factoryMock;
    ModuleRegistry registry;
    EXPECT_CALL(factoryMock, createSyntax).WillOnce(Return(ByMove(std::unique_ptr<IModule>(new Module("Lang.Syntax")))));
    EXPECT_CALL(factoryMock, createLists).WillOnce(Return(ByMove(std::unique_ptr<IModule>(new Module("Lang.Lists")))));
    EXPECT_CALL(factoryMock, createCompare).WillOnce(Return(ByMove(std::unique_ptr<IModule>(new Module("Lang.Compare")))));
    EXPECT_CALL(factoryMock, createArithmetic).WillOnce(Return(ByMove(std::unique_ptr<IModule>(new Module("Lang.Arithmetic")))));
    BuiltinsBuilder builtinsBuilder(registry, factoryMock);
    builtinsBuilder.build();
}

}