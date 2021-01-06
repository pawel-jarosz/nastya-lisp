//
// Created by caedus on 31.12.2020.
//

#include <LispExpression/ObjectStorageException.hpp>
#include <LispExpression/TypeSystem/NumberObject.hpp>

#include <But/Format/format.hpp>
#include <But/Format/apply.hpp>

#include "ConsoleManager.hpp"

namespace nastya::cli {

std::string toString(const lisp::ObjectStorage& object)
{
    std::stringstream ss;
    if (object.getType() == lisp::ObjectType::Number)
    {
        auto as_number = dynamic_cast<lisp::typesystem::NumberObject&>(object.getRawObject());
        if (as_number.getNumberType() == lisp::NumberType::Floating)
        {
            ss << "Floating => ";
        }
        else
        {
            ss << "Integer => ";
        }
    }
    switch (object.getType())
    {
        case lisp::ObjectType::Boolean:
            ss << "Boolean => ";
            break;
        case lisp::ObjectType::String:
            ss << "String => ";
            break;
        case lisp::ObjectType::List:
            ss << "List => ";
            break;
        case lisp::ObjectType::Label:
            ss << "Label => ";
            break;
    }
    ss << object.toString();
    return ss.str();
}

ConsoleManager::ConsoleManager(vm::Machine& machine,
                               parser::IParser& parser,
                               lisp::IExpressionBuilder& expression_builder,
                               io::IIoFactory& io_provider)
: m_machine{machine}, m_parser{parser}, m_expr_builder{expression_builder}
, m_in{io_provider.create_input()}, m_out{io_provider.create_output()}
{
}

void ConsoleManager::splashScreen()
{
    m_out->writeLine("\t  __________________________________");
    m_out->writeLine("\t |                                  |");
    m_out->writeLine("\t | Nastya Lisp                      |");
    m_out->writeLine("\t | v. 2021.0.1                      |");
    m_out->writeLine("\t |__________________________________|\n");
}

int ConsoleManager::run()
{
    auto result_format = BUT_FORMAT("  | $0");
    std::stringstream ss;
    bool multiline = false;
    do
    {
        if (not multiline)
        {
            m_out->write("? | ");
        }
        std::string line = m_in->readLine();

        if (line == "")
        {
            continue;
        }
        ss << line << " ";
        m_parser.reset(ss.str());
        m_expr_builder.reset();
        try
        {
            auto expression = m_expr_builder.build();
            auto result = m_machine.run(expression);
            if (not m_shutdown)
            {
                m_out->writeLine(But::Format::apply(result_format, toString(result)));
                std::stringstream empty_stream;
                ss.swap(empty_stream);
            }
            multiline = false;
        }
        catch (nastya::lisp::ObjectStorageException& e)
        {
            multiline = true;
            continue;
        }
        catch (std::runtime_error& error)
        {
        }
    } while (not m_shutdown);
    m_parser.reset(ss.str());
    return 0;
}
void ConsoleManager::shutdown()
{
    m_shutdown = true;
}

}  // namespace nastya::cli
