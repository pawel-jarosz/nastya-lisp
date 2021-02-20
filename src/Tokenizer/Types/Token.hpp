//
// Created by caedus on 03.12.2020.
//

#pragma once

#include <map>
#include <sstream>
#include <string>
#include <variant>

namespace nastya::tokens {

using TokenValue = std::variant<bool, int, float, std::string>;

enum class TokenType
{
    Label,
    Boolean,
    Integer,
    Floating,
    String,
    S_expr_begin,
    S_expr_end,
    Quote,
    Eof
};

struct Token
{
    TokenType type;
    TokenValue value;
};

struct Converter {
    static const std::map<TokenType, std::string> conversion_map;
};

std::ostream& operator<<(std::ostream& out, const TokenType& type);

std::ostream& operator<<(std::ostream& out, const Token& token);

bool operator==(const Token& lhs, const Token& rhs);

}  // namespace nastya::tokens
