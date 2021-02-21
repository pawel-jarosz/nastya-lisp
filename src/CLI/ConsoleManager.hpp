//
// Created by caedus on 31.12.2020.
//

#pragma once

#include "CLI/Interface/IConsoleManager.hpp"
#include "CLI/Interface/IIoFactory.hpp"
#include "CLI/Interface/ISplashScreen.hpp"
#include "Parser/Interface/IParser.hpp"
#include "Runtime/Interface/IMachine.hpp"
#include "Tokenizer/Interface/ITokenizer.hpp"

namespace nastya::cli {

class ConsoleManager : public interface::IConsoleManager
{
public:
    ConsoleManager(runtime::IMachine& machine,
                   tokens::ITokenizer& parser,
                   parser::IParser& expression_builder,
                   io::IIoFactory& io_provider,
                   splashscreen::ISplashScreen& splash_screen);
    void splashScreen();
    int run() override;
    void shutdown() override;

private:
    runtime::IMachine& m_machine;
    tokens::ITokenizer& m_parser;
    parser::IParser& m_expr_builder;
    But::NotNullUnique<io::IInputSource> m_in;
    But::NotNullUnique<io::IOutputSink> m_out;
    splashscreen::ISplashScreen& m_splashscreen;
    bool m_shutdown;
};
}  // namespace nastya::cli