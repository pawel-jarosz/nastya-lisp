//
// Created by caedus on 02.01.2021.
//

#include <stdexcept>

#include "ConsoleEvaluators.hpp"

namespace nastya::cli::module {

ShutdownEvaluator::ShutdownEvaluator(interface::IConsoleManager& console) : m_console{console}
{
}

lisp::ObjectStorage ShutdownEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const
{
    m_console.shutdown();
    throw std::runtime_error("Shutdown event");
}
}  // namespace nastya::cli::module