//
// Created by caedus on 31.12.2020.
//

#pragma once

#include "CLI/Interface/IConsoleManager.hpp"
#include "CLI/Interface/IIoFactory.hpp"
#include "LispExpression/Interface/IExpressionBuilder.hpp"
#include "Parser/Interface/IParser.hpp"
#include "VirtualMachine/Machine.hpp"

namespace nastya::cli {

class ConsoleManager : public interface::IConsoleManager
{
public:
    ConsoleManager(nastya::vm::Machine& machine,
                   nastya::parser::IParser& parser,
                   nastya::lisp::IExpressionBuilder& expression_builder,
                   io::IIoFactory& io_provider);
    void splashScreen();
    int run() override;
    void shutdown() override;

private:
    nastya::vm::Machine& m_machine;
    nastya::parser::IParser& m_parser;
    nastya::lisp::IExpressionBuilder& m_expr_builder;
    But::NotNullUnique<io::IInputSource> m_in;
    But::NotNullUnique<io::IOutputSink> m_out;
    bool m_shutdown;
};
}  // namespace nastya::cli