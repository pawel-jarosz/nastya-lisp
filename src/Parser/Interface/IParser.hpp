//
// Created by caedus on 03.12.2020.
//

#pragma once

#include "Parser/Types/Token.hpp"

namespace nastya::parser {

    class IParser {
    public:
        IParser() = default;
        virtual Token getToken() = 0;
        virtual bool isEmpty() = 0;
        virtual void reset(std::string code) = 0;
    };

}
