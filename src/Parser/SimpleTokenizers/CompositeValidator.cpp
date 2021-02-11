//
// Created by caedus on 11.02.2021.
//

#include "Parser/SimpleTokenizers/CompositeValidator.hpp"

namespace nastya::parser {

CompositeValidator::CompositeValidator()
{
}

CompositeValidator& CompositeValidator::addValidator(std::unique_ptr<IValidator> validator)
{
    m_validators.emplace_back(std::move(validator));
    return *this;
}

std::optional<Token> CompositeValidator::validate(const std::string& value, ParsingContext& context) const {
    for (const auto& validator: m_validators) {
        const auto result = validator->validate(value, context);
        if (result) {
            return *result;
        }
    }
    return {};
}

}
