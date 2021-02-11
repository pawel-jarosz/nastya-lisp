//
// Created by caedus on 11.02.2021.
//

#pragma once

#include "Parser/Interface/IValidator.hpp"
#include <memory>
#include <vector>

namespace nastya::parser {

class CompositeValidator : public IValidator {
public:
    CompositeValidator();
    CompositeValidator& addValidator(std::unique_ptr<IValidator> validator);
    std::optional<Token> validate(const std::string& value, ParsingContext& context) const override;
private:
    std::vector<std::unique_ptr<IValidator>> m_validators;
};

}
