//
// Created by caedus on 11.02.2021.
//

#pragma once

#include <memory>

#include "Parser/TokenProviders/TokenProvidersAggregator.hpp"

namespace nastya::parser {

class AtomicValueTokenProvider : public TokenProvidersAggregator
{
public:
    AtomicValueTokenProvider() = default;
    std::optional<Token> getTokenIfAvailable(const std::string& value, ParsingContext& context) const override;
    static std::unique_ptr<ITokenProvider> create();
};

}
