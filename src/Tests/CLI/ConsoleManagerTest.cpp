//
// Created by caedus on 06.01.2021.
//

#include <thread>

#include <gtest/gtest.h>

#include "Builtins/BuiltinsBuilder.hpp"
#include "CLI/ConsoleManager.hpp"
#include "CLI/Testing/InputSourceMock.hpp"
#include "CLI/Testing/IoFactoryMock.hpp"
#include "CLI/Testing/OutputSinkMock.hpp"
#include "CLI/Testing/SplashScreenMock.hpp"
#include "Modules/ModuleRegistry.hpp"
#include "Parser/Testing/ExpressionBuilderMock.hpp"
#include "Parser/Testing/ListBuilder.hpp"
#include "Runtime/Testing/MachineMock.hpp"
#include "Tokenizer/Testing/ParserMock.hpp"
#include "VirtualMachine/Machine.hpp"

namespace nastya::cli {
using namespace ::testing;

TEST(ConsoleManagerTest, testSplashScreen)
{
    runtime::MachineMock machine;
    tokens::ParserMock parser;
    lisp::testing::ExpressionBuilderMock expression_builder;
    io::IoFactoryMock io_factory;
    auto output = new io::OutputSinkMock();
    splashscreen::SplashScreenMock splashscreen;
    std::vector<std::string> message = {"Screensplash message"};
    EXPECT_CALL(io_factory, create_output()).WillOnce(Return(ByMove(But::NotNullUnique<io::IOutputSink>(output))));
    EXPECT_CALL(io_factory, create_input())
        .WillOnce(Return(ByMove(But::NotNullUnique<io::IInputSource>(new io::InputSourceMock()))));
    EXPECT_CALL(*output, writeLine(message[0]));
    ConsoleManager console_manager(machine, parser, expression_builder, io_factory, splashscreen);

    EXPECT_CALL(splashscreen, getMessage()).WillOnce(ReturnRef(message));
    console_manager.splashScreen();
}

}  // namespace nastya::cli
