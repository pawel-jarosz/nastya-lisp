//
// Created by caedus on 11.02.2021.
//

#include "Parser/TokenProviders/TokenProvidersAggregator.hpp"

namespace nastya::parser {

TokenProvidersAggregator::TokenProvidersAggregator()
{
}

TokenProvidersAggregator& TokenProvidersAggregator::addValidator(std::unique_ptr<ITokenProvider> validator)
{
    m_validators.emplace_back(std::move(validator));
    return *this;
}

std::optional<Token> TokenProvidersAggregator::getTokenIfAvailable(const std::string& value, ParsingContext& context) const {
    for (const auto& validator: m_validators) {
        const auto result = validator->getTokenIfAvailable(value, context);
        if (result) {
            return *result;
        }
    }
    return {};
}

}
