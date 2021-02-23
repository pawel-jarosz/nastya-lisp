//
// Created by caedus on 02.01.2021.
//

#pragma once

#include "CLI/Interface/IConsoleManager.hpp"
#include "Runtime/GenericEvaluator.hpp"

namespace nastya::cli::module {

class ShutdownEvaluator : public runtime::GenericEvaluator
{
public:
    ShutdownEvaluator(interface::IConsoleManager& console);
    typesystem::ObjectStorage evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const override;

private:
    interface::IConsoleManager& m_console;
};

}  // namespace nastya::cli::module
