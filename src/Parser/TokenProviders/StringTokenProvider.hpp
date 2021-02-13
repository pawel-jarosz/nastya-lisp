//
// Created by caedus on 11.02.2021.
//

#include <memory>

#include "Parser/Interface/ITokenProvider.hpp"

#pragma once

namespace nastya::parser {

class StringTokenProvider : public ITokenProvider
{
public:
    StringTokenProvider();
    std::optional<Token> getTokenIfAvailable(const std::string& value, ParsingContext& context) const override;
    static std::unique_ptr<ITokenProvider> create();
};

}
