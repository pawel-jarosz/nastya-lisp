//
// Created by caedus on 09.02.2021.
//

#pragma once

#include <functional>
#include <memory>
#include <optional>

#include "Parser/Interface/ITokenProvider.hpp"
#include "Parser/Types/Token.hpp"

namespace nastya::parser {

using NumberFactory = std::function<std::optional<Token>(const std::string& value)>;

const std::string INTEGER_REGEX = "(-)?[0-9]+";
const std::string FLOATING_REGEX = "(-)?[0-9]+\\.[0-9]+(e(-)?[0-9]+)?(f|d)?";

class NumberTokenProvider : public ITokenProvider
{
public:
    NumberTokenProvider() = default;
    void addType(std::string regex, NumberFactory factory);
    std::optional<Token> getTokenIfAvailable(const std::string& value, ParsingContext& context) const override;
    static std::unique_ptr<ITokenProvider> create();
private:
    std::vector<std::pair<std::string, NumberFactory>> m_factories;
};

std::optional<Token> parse_float(const std::string& value);
std::optional<Token> parse_integer(const std::string& value);

}
