//
// Created by caedus on 12.12.2020.
//

#pragma once

namespace nastya::typesystem {

enum ObjectType
{
    Boolean,
    Number,
    String,
    Label,
    List,
    Lambda
};

enum class NumberType
{
    Floating,
    Integer
};

}  // namespace nastya::parser