//
// Created by caedus on 11.02.2021.
//

#include <memory>

#include "Tokenizer/Interface/ITokenProvider.hpp"

#pragma once

namespace nastya::tokens {

class StringTokenProvider : public ITokenProvider
{
public:
    StringTokenProvider();
    std::optional<Token> getTokenIfAvailable(const std::string& value, ParsingContext& context) const override;
    static std::unique_ptr<ITokenProvider> create();
};

}
