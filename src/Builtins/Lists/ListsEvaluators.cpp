//
// Created by caedus on 21.12.2020.
//

#include "LispExpression/TypeSystem/ListObject.hpp"
#include "Builtins/BuiltinsException.hpp"
#include "ListsEvaluators.hpp"

namespace nastya::builtins::lists {
lisp::ObjectStorage HeadEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const
{
    if (object.getType() != lisp::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Lists.Head expects list of arguments");
    }
    const auto& arguments_list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 1) {
        BUT_THROW(BuiltinsException, "Lang.Lists.Head expects exactly one argument");
    }
    const auto first_argument = arguments_list.getContent()[0];
    if (first_argument.getType() != lisp::ObjectType::List) {
        BUT_THROW(BuiltinsException, "Lang.Lists.Head expects list as an argument");
    }
    const auto as_list = dynamic_cast<lisp::typesystem::ListObject&>(first_argument.getRawObject()).getContent();
    if (as_list.empty()) {
        BUT_THROW(BuiltinsException, "Lang.Lists.Head expects not empty list as an argument");
    }
    return as_list[0];
}

lisp::ObjectStorage TailEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const
{
    if (object.getType() != lisp::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Lists.Tail expects list of arguments");
    }

    const auto& arguments_list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 1) {
        BUT_THROW(BuiltinsException, "Lang.Lists.Tail expects exactly one argument");
    }
    const auto first_argument = arguments_list.getContent()[0];
    if (first_argument.getType() != lisp::ObjectType::List) {
        BUT_THROW(BuiltinsException, "Lang.Lists.Tail expects list as an argument");
    }
    const auto as_list = dynamic_cast<lisp::typesystem::ListObject&>(first_argument.getRawObject()).getContent();
    if (as_list.empty()) {
        BUT_THROW(BuiltinsException, "Lang.Lists.Tail expects list with more then one element");
    }
    std::vector<lisp::ObjectStorage> tail(++as_list.begin(), as_list.end());
    return lisp::ObjectStorage(std::unique_ptr<lisp::IObject>(new lisp::typesystem::ListObject(tail)));
}

lisp::ObjectStorage QuoteEvaluator::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const
{
    if (object.getType() != lisp::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Lists.Quote expects list of arguments");
    }
    auto arguments_list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 1) {
        BUT_THROW(BuiltinsException, "Lang.Lists.Quote expects exactly one argument");
    }
    return lisp::ObjectStorage(arguments_list.getContent()[0]);
}
}  // namespace nastya::builtins::lists
