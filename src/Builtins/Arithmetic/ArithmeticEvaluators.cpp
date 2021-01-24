//
// Created by caedus on 23.01.2021.
//
#include "LispExpression/TypeSystem/ListObject.hpp"
#include "Builtins/BuiltinsException.hpp"
#include "Utilities/LispCast.hpp"
#include "ArithmeticEvaluators.hpp"

#include <algorithm>

#define ASSERT_THROW(condition, msg)              \
        if (condition) {                          \
            BUT_THROW(BuiltinsException, msg);    \
         }

namespace nastya::builtins::arithmetic {

using namespace utils;

lisp::ObjectStorage AddEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const
{
    const auto& arguments_list = Cast::as_list(object, "Lang.Arithmetic.Add expects list of arguments");
    bool is_integer_sum = true;
    union {
        int integer_sum = 0;
        float float_sum;
    } sum;

    for (const auto number_object: arguments_list.getContent()) {
        const auto& number = utils::Cast::as_number(number_object, "Lang.Arithmetic.Add expects number");
        if (is_integer_sum and number.getNumberType() == lisp::NumberType::Floating) {
            sum.float_sum = sum.integer_sum;
            is_integer_sum = false;
        }
        if (is_integer_sum) {
            sum.integer_sum += number.getInteger();
        }
        else {
            sum.float_sum += number.getFloating();
        }
    }
    auto result_pointer = (is_integer_sum ? (new lisp::typesystem::NumberObject(sum.integer_sum))
                                          : (new lisp::typesystem::NumberObject(sum.float_sum)));
    lisp::ObjectStorage result{std::unique_ptr<lisp::IObject>(result_pointer)};
    return  result;
}

}
