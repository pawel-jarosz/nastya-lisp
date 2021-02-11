//
// Created by caedus on 11.02.2021.
//

#include "Parser/Interface/IValidator.hpp"

#pragma once

namespace nastya::parser {

class StringValidator : public IValidator {
public:
    StringValidator();
    std::optional<Token> validate(const std::string& value, ParsingContext& context) const override;
};

}
