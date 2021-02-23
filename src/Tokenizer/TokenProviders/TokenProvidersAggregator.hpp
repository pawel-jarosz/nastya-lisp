//
// Created by caedus on 11.02.2021.
//

#pragma once

#include <memory>
#include <vector>

#include "Tokenizer/Interface/ITokenProvider.hpp"

namespace nastya::tokens {

class TokenProvidersAggregator : public ITokenProvider
{
public:
    TokenProvidersAggregator();
    TokenProvidersAggregator& addProvider(std::unique_ptr<ITokenProvider> validator);
    std::optional<Token> getTokenIfAvailable(const std::string& value, ParsingContext& context) const override;
private:
    std::vector<std::unique_ptr<ITokenProvider>> m_validators;
};

}
