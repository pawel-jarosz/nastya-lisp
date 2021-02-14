//
// Created by caedus on 03.12.2020.
//

#pragma once

#include "Tokenizer/Types/Token.hpp"

namespace nastya::tokens {

class ITokenizer
{
public:
    ~ITokenizer() = default;
    virtual Token getToken() = 0;
    virtual void reset(std::string code) = 0;
};

}  // namespace nastya::tokens
