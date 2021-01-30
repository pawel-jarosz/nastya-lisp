//
// Created by caedus on 02.01.2021.
//

#include "CLI/Module/ShutdownEvent.hpp"
#include "ConsoleEvaluators.hpp"

namespace nastya::cli::module {

ShutdownEvaluator::ShutdownEvaluator(interface::IConsoleManager& console)
:runtime::GenericEvaluator("Exit-Console")
, m_console{console}
{
}

lisp::ObjectStorage ShutdownEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const
{
    m_console.shutdown();
    BUT_THROW(ShutdownEvent, "Close event sent");
}
}  // namespace nastya::cli::module