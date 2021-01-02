//
// Created by caedus on 02.01.2021.
//

#include "ConsoleEvaluators.hpp"

#include <stdexcept>

namespace nastya::cli::module {

ShutdownEvaluator::ShutdownEvaluator(nastya::cli::interface::IConsoleManager& console)
: m_console{console}
{
}

lisp::ObjectStorage ShutdownEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const
{
    m_console.shutdown();
    throw std::runtime_error("Shutdown event");
}
}