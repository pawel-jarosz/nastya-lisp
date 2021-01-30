//
// Created by caedus on 21.12.2020.
//

#include "LispExpression/TypeSystem/ListObject.hpp"
#include "Builtins/BuiltinsException.hpp"
#include "Utilities/LispCast.hpp"
#include "ListsEvaluators.hpp"

#define ASSERT_THROW(condition, msg)              \
        if (condition) {                          \
            BUT_THROW(BuiltinsException, msg);    \
         }

namespace nastya::builtins::lists {

using namespace utils;

lisp::ObjectStorage HeadEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const
{
    const auto& arguments_list = Cast::as_list(object, "Lang.Lists.Head expects list of arguments");
    ASSERT_THROW(arguments_list.getSize() != 1, "Lang.Lists.Head expects exactly one argument");
    const auto first_argument = arguments_list.getContent()[0];
    const auto as_list = Cast::as_list(first_argument).getContent();
    ASSERT_THROW(as_list.empty(), "Lang.Lists.Head expects not empty list as an argument")
    return as_list[0];
}

lisp::ObjectStorage TailEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const
{
    const auto& arguments_list = Cast::as_list(object, "Lang.Lists.Tail expects list of arguments");
    ASSERT_THROW(arguments_list.getSize() != 1, "Lang.Lists.Tail expects exactly one argument");
    const auto first_argument = arguments_list.getContent()[0];
    const auto as_list = Cast::as_list(first_argument, "Lang.Lists.Tail expects list as an argument").getContent();
    ASSERT_THROW(as_list.empty(), "Lang.Lists.Tail expects list with more then one element");
    std::vector<lisp::ObjectStorage> tail(++as_list.begin(), as_list.end());
    return lisp::ObjectStorage(std::unique_ptr<lisp::IObject>(new lisp::typesystem::ListObject(tail)));
}

lisp::ObjectStorage QuoteEvaluator::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const
{
    const auto& arguments_list = Cast::as_list(object, "Lang.Lists.Quote expects list of arguments");
    ASSERT_THROW(arguments_list.getSize() != 1, "Lang.Lists.Quote expects exactly one argument");
    return lisp::ObjectStorage(arguments_list.getContent()[0]);
}

lisp::ObjectStorage QuoteEvaluator::preExecute(const lisp::typesystem::ListObject& object, runtime::IMachine& vm) const
{
    const auto content = object.getContent();
    std::vector<lisp::ObjectStorage> arguments(++content.begin(), content.end());
    std::unique_ptr<lisp::IObject> obj(new lisp::typesystem::ListObject(arguments));
    lisp::ObjectStorage result(std::move(obj));
    return result;
}
}  // namespace nastya::builtins::lists
