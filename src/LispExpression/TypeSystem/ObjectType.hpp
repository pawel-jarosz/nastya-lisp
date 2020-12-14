//
// Created by caedus on 12.12.2020.
//

#pragma once

namespace nastya::lisp {

enum ObjectType {
    Boolean,
    Number,
    String,
    Label,
    List
};

enum class NumberType {
    Floating,
    Integer
};

}