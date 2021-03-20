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

enum class ResultType {
    Floating,
    Integer,
    Unknown
};

class Sumator {
public:
    Sumator() = default;
    Sumator& operator+(int integer);
    Sumator& operator+(float floating);
    typesystem::NumberObject getResult() const;
private:
    union {
        int integer_sum = 0;
        float float_sum;
    };
    ResultType sum_result = ResultType::Integer;
};

Sumator& Sumator::operator+(int integer)
{
    if (sum_result == ResultType::Integer) {
        integer_sum += integer;
    }
    else {
        float_sum += integer;
    }
    return *this;
}

Sumator& Sumator::operator+(float floating)
{
    if (sum_result == ResultType::Integer) {
        sum_result = ResultType::Floating;
        float temp = integer_sum;
        temp += floating;
        float_sum = temp;
    }
    else {
        float_sum += floating;
    }
    return *this;
}

typesystem::NumberObject Sumator::getResult() const
{
    if (sum_result == ResultType::Integer) {
        return typesystem::NumberObject(integer_sum);
    }
    return typesystem::NumberObject(float_sum);
}

typesystem::ObjectStorage AddEvaluator::evaluate(runtime::IMemory&, const typesystem::ObjectStorage& object) const
{
    const auto& arguments_list = Cast::as_list(object, "Lang.Arithmetic.Add expects list of arguments");
    Sumator sum;

    for (const auto number_object : arguments_list.getContent())
    {
        const auto& number = utils::Cast::as_number(number_object, "Lang.Arithmetic.Add expects number");
        if (number.getNumberType() == typesystem::NumberType::Floating)
        {
            sum = sum + number.getFloating();
        }
        else {
            sum = sum + number.getInteger();
        }
    }

    typesystem::ObjectStorage result{std::unique_ptr<typesystem::IObject>(sum.getResult().clone())};
    return result;
}

class Subtractor {
public:
    Subtractor() = default;
    Subtractor& operator-(int integer);
    Subtractor& operator-(float floating);
    typesystem::NumberObject getResult() const;
private:
    union {
        int integer_subtraction = 0;
        float float_subtraction;
    };
    ResultType subtraction_result = ResultType::Unknown;
};

Subtractor& Subtractor::operator-(int integer)
{
    if (subtraction_result == ResultType::Unknown) {
        integer_subtraction = integer;
        subtraction_result = ResultType::Integer;
        return *this;
    }
    if (subtraction_result == ResultType::Integer) {
        integer_subtraction -= integer;
    }
    else {
        float_subtraction -= integer;
    }
    return *this;
}

Subtractor& Subtractor::operator-(float floating)
{
    if (subtraction_result == ResultType::Unknown) {
        float_subtraction = floating;
        subtraction_result = ResultType::Floating;
        return *this;
    }
    if (subtraction_result == ResultType::Integer) {
        subtraction_result = ResultType::Floating;
        float temp = integer_subtraction;
        temp -= floating;
        float_subtraction = temp;
    }
    else {
        float_subtraction -= floating;
    }
    return *this;
}

typesystem::NumberObject Subtractor::getResult() const
{
    if (subtraction_result == ResultType::Integer) {
        return typesystem::NumberObject(integer_subtraction);
    }
    return typesystem::NumberObject(float_subtraction);
}

typesystem::ObjectStorage
SubtractionEvaluator::evaluate(runtime::IMemory&, const typesystem::ObjectStorage& object) const
{
    const auto& arguments_list = Cast::as_list(object, "Lang.Arithmetic.Add expects list of arguments");
    Subtractor subtractor;

    for (const auto number_object : arguments_list.getContent())
    {
        const auto& number = utils::Cast::as_number(number_object, "Lang.Arithmetic.Add expects number");
        if (number.getNumberType() == typesystem::NumberType::Floating)
        {
            subtractor = subtractor - number.getFloating();
        }
        else {
            subtractor = subtractor - number.getInteger();
        }
    }
    typesystem::ObjectStorage result{std::unique_ptr<typesystem::IObject>(subtractor.getResult().clone())};
    return result;
}

}  // namespace nastya::builtins::arithmetic
