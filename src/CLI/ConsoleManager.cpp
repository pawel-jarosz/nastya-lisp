//
// Created by caedus on 31.12.2020.
//

#include <iostream>

#include <LispExpression/ObjectStorageException.hpp>

#include "ConsoleManager.hpp"

namespace nastya::cli {

ConsoleManager::ConsoleManager(vm::Machine& machine,
                               parser::IParser& parser,
                               lisp::IExpressionBuilder& expression_builder)
: m_machine{machine}
, m_parser{parser}
, m_expr_builder{expression_builder}
{
}

void ConsoleManager::splashScreen() {

}

int ConsoleManager::run() {
    std::stringstream ss;
    do {
        std::cout << "? | ";
        std::string line;
        getline(std::cin, line);
        ss << line << " ";
        m_parser.reset(ss.str());
        m_expr_builder.reset();
        try {
            auto expression = m_expr_builder.build();
            auto result = m_machine.run(expression);
            if (not m_shutdown) {
                std::cout << result.toString() << std::endl;
                std::stringstream empty_stream;
                ss.swap(empty_stream);
            }
        }
        catch (nastya::lisp::ObjectStorageException& e) {
            continue;
        }
        catch (std::runtime_error& error) {

        }
    }
    while (not m_shutdown);
    m_parser.reset(ss.str());
    return 0;
}
void ConsoleManager::shutdown()
{
    m_shutdown = true;
}

}
