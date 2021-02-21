//
// Created by caedus on 11.02.2021.
//

#include "Tokenizer/TokenProviders/TokenProvidersAggregator.hpp"

namespace nastya::tokens {

TokenProvidersAggregator::TokenProvidersAggregator()
{
}

TokenProvidersAggregator& TokenProvidersAggregator::addProvider(std::unique_ptr<ITokenProvider> validator)
{
    m_validators.emplace_back(std::move(validator));
    return *this;
}

std::optional<Token>
TokenProvidersAggregator::getTokenIfAvailable(const std::string& value, ParsingContext& context) const
{
    for (const auto& validator : m_validators)
    {
        const auto result = validator->getTokenIfAvailable(value, context);
        if (result)
        {
            return *result;
        }
    }
    return {};
}

}  // namespace nastya::tokens
