//
// Created by caedus on 11.02.2021.
//

#include "Parser/Interface/IValidator.hpp"
#include <memory>

#pragma once

namespace nastya::parser {

class StringValidator : public IValidator {
public:
    StringValidator();
    std::optional<Token> validate(const std::string& value, ParsingContext& context) const override;
    static std::unique_ptr<IValidator> create();
};

}
