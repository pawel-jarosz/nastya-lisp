//
// Created by caedus on 23.01.2021.
//
#include <algorithm>

#include "ArithmeticEvaluators.hpp"
#include "Builtins/BuiltinsException.hpp"
#include "TypeSystem/Types/ListObject.hpp"
#include "Utilities/LispCast.hpp"

#define ASSERT_THROW(condition, msg) \
    if (condition) \
    { \
        BUT_THROW(BuiltinsException, msg); \
    }

namespace nastya::builtins::arithmetic {

using namespace utils;

typesystem::ObjectStorage AddEvaluator::evaluate(runtime::IMemory&, const typesystem::ObjectStorage& object) const
{
    const auto& arguments_list = Cast::as_list(object, "Lang.Arithmetic.Add expects list of arguments");
    bool is_integer_sum = true;
    union
    {
        int integer_sum = 0;
        float float_sum;
    } sum;

    for (const auto number_object : arguments_list.getContent())
    {
        const auto& number = utils::Cast::as_number(number_object, "Lang.Arithmetic.Add expects number");
        if (is_integer_sum and number.getNumberType() == typesystem::NumberType::Floating)
        {
            sum.float_sum = sum.integer_sum;
            is_integer_sum = false;
        }
        if (is_integer_sum)
        {
            sum.integer_sum += number.getInteger();
        }
        else
        {
            sum.float_sum += number.getFloating();
        }
    }
    auto result_pointer = (is_integer_sum ? (new typesystem::NumberObject(sum.integer_sum))
                                          : (new typesystem::NumberObject(sum.float_sum)));
    typesystem::ObjectStorage result{std::unique_ptr<typesystem::IObject>(result_pointer)};
    return result;
}

typesystem::ObjectStorage
SubtractionEvaluator::evaluate(runtime::IMemory&, const typesystem::ObjectStorage& object) const
{
    const auto& arguments_list = Cast::as_list(object, "Lang.Arithmetic.Add expects list of arguments");
    bool is_integer_sum = true;
    union
    {
        int integer_sum = 0;
        float float_sum;
    } sum;

    for (const auto number_object : arguments_list.getContent())
    {
        const auto& number = utils::Cast::as_number(number_object, "Lang.Arithmetic.Add expects number");
        if (is_integer_sum and number.getNumberType() == typesystem::NumberType::Floating)
        {
            sum.float_sum = sum.integer_sum;
            is_integer_sum = false;
        }
        if (is_integer_sum)
        {
            sum.integer_sum -= number.getInteger();
        }
        else
        {
            sum.float_sum -= number.getFloating();
        }
    }
    auto result_pointer = (is_integer_sum ? (new typesystem::NumberObject(sum.integer_sum))
                                          : (new typesystem::NumberObject(sum.float_sum)));
    typesystem::ObjectStorage result{std::unique_ptr<typesystem::IObject>(result_pointer)};
    return result;
}

}  // namespace nastya::builtins::arithmetic
