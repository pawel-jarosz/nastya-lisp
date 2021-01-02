//
// Created by caedus on 31.12.2020.
//

#pragma once

#include "VirtualMachine/Machine.hpp"
#include "CLI/Interface/IConsoleManager.hpp"
#include "Parser/Interface/IParser.hpp"
#include "LispExpression/Interface/IExpressionBuilder.hpp"

namespace nastya::cli {

class ConsoleManager : public interface::IConsoleManager {
public:
    ConsoleManager(nastya::vm::Machine& machine,
                   nastya::parser::IParser& parser,
                   nastya::lisp::IExpressionBuilder& expression_builder);
    void splashScreen();
    int run() override;
    void shutdown() override;
private:
    nastya::vm::Machine& m_machine;
    nastya::parser::IParser& m_parser;
    nastya::lisp::IExpressionBuilder& m_expr_builder;
    bool m_shutdown;
};
}