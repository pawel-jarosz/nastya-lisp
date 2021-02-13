//
// Created by caedus on 31.12.2020.
//

#pragma once

#include "CLI/Interface/IConsoleManager.hpp"
#include "CLI/Interface/IIoFactory.hpp"
#include "CLI/Interface/ISplashScreen.hpp"
#include "LispExpression/Interface/IExpressionBuilder.hpp"
#include "Runtime/Interface/IMachine.hpp"
#include "Tokenizer/Interface/ITokenizer.hpp"

namespace nastya::cli {

class ConsoleManager : public interface::IConsoleManager
{
public:
    ConsoleManager(runtime::IMachine& machine,
                   parser::ITokenizer& parser,
                   lisp::IExpressionBuilder& expression_builder,
                   io::IIoFactory& io_provider,
                   splashscreen::ISplashScreen& splash_screen);
    void splashScreen();
    int run() override;
    void shutdown() override;

private:
    runtime::IMachine& m_machine;
    parser::ITokenizer& m_parser;
    lisp::IExpressionBuilder& m_expr_builder;
    But::NotNullUnique<io::IInputSource> m_in;
    But::NotNullUnique<io::IOutputSink> m_out;
    splashscreen::ISplashScreen& m_splashscreen;
    bool m_shutdown;
};
}  // namespace nastya::cli