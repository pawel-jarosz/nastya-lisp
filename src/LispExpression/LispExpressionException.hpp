//
// Created by caedus on 27.12.2020.
//

#pragma once

#include <But/Exception.hpp>

namespace nastya::lisp {

BUT_DEFINE_EXCEPTION(LispExpressionException, But::Exception, "LispExpression");

}