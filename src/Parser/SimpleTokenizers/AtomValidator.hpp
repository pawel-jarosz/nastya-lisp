//
// Created by caedus on 11.02.2021.
//

#pragma once

#include "Parser/SimpleTokenizers/CompositeValidator.hpp"

namespace nastya::parser {

class AtomValidator : public CompositeValidator {
public:
    AtomValidator() = default;
    std::optional<Token> validate(const std::string& value, ParsingContext& context) const override;
};

}
