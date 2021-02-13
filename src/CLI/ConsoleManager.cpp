//
// Created by caedus on 31.12.2020.
//

#include <But/Format/apply.hpp>
#include <But/Format/format.hpp>

#include "CLI/ConsoleManager.hpp"
#include "CLI/Module/ShutdownEvent.hpp"
#include "TypeSystem/Types/NumberObject.hpp"
#include "TypeSystem/Types/TypeSystemError.hpp"
#include "TypeSystem/ObjectStorageException.hpp"
#include "VirtualMachine/MachineRuntimeException.hpp"

namespace nastya::cli {

ConsoleManager::ConsoleManager(runtime::IMachine& machine,
                               parser::ITokenizer& parser,
                               lisp::IExpressionBuilder& expression_builder,
                               io::IIoFactory& io_provider,
                               splashscreen::ISplashScreen& splash_screen)
: m_machine{machine}, m_parser{parser}, m_expr_builder{expression_builder}
, m_in{io_provider.create_input()}, m_out{io_provider.create_output()}
, m_splashscreen{splash_screen}
, m_shutdown{false}
{
}

void ConsoleManager::splashScreen()
{
    const auto message_lines = m_splashscreen.getMessage();
    for (const auto& message: message_lines) {
        m_out->writeLine(message);
    }
}

int ConsoleManager::run()
{
    // GCOVR_EXCL_START
    //
    // To be handled by manual test
    auto result_format = BUT_FORMAT("  | $0");
    std::stringstream ss;
    bool multiline = false;
    while (not m_shutdown)
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
                m_out->writeLine(But::Format::apply(result_format, result.getRawObject().info()));
                std::stringstream empty_stream;
                ss.swap(empty_stream);
            }
            multiline = false;
        }
        catch(lisp::typesystem::TypeSystemError& e) {
            m_out->writeLine(e.what());
        }
        catch (vm::MachineRuntimeException& e) {
            m_out->writeLine(e.what());
        }
        catch (lisp::ObjectStorageException& e)
        {
            multiline = true;
            continue;
        }
        catch (module::ShutdownEvent& e)
        {
            return 0;
        }
        catch (std::exception& error)
        {
            m_out->writeLine(error.what());
        }
    }
    m_parser.reset(ss.str());
    // GCOVR_EXCL_STOP
    return 0;
}
void ConsoleManager::shutdown()
{
    m_shutdown = true;
}

}  // namespace nastya::cli
