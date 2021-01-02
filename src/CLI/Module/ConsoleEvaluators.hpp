//
// Created by caedus on 02.01.2021.
//

#pragma once

#include "CLI/Interface/IConsoleManager.hpp"
#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::cli::module {

class ShutdownEvaluator : public runtime::IEvaluator {
public:
    ShutdownEvaluator(interface::IConsoleManager& console);
    std::string getName() const  override { return "Exit-Console"; }
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const;
private:
    interface::IConsoleManager& m_console;
};

}
