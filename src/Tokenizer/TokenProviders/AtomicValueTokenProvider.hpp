//
// Created by caedus on 11.02.2021.
//

#pragma once

#include <memory>

#include "Tokenizer/TokenProviders/TokenProvidersAggregator.hpp"

namespace nastya::tokens {

class AtomicValueTokenProvider : public TokenProvidersAggregator
{
public:
    AtomicValueTokenProvider();
    std::optional<Token> getTokenIfAvailable(const std::string& value, ParsingContext& context) const override;
    static std::unique_ptr<ITokenProvider> create();
};

}
