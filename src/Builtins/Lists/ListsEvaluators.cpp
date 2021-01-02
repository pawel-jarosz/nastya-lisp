//
// Created by caedus on 21.12.2020.
//

#include "LispExpression/TypeSystem/ListObject.hpp"
#include "ListsEvaluators.hpp"

namespace nastya::builtins::lists {
lisp::ObjectStorage HeadEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const
{
    if (object.getType() == lisp::ObjectType::List)
    {
        // TODO: Error handling
        const auto& arguments_list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
        const auto first_argument = arguments_list.getContent()[0];
        const auto as_list = dynamic_cast<lisp::typesystem::ListObject&>(first_argument.getRawObject()).getContent();
        return as_list[0];
    }
    throw;
}

lisp::ObjectStorage TailEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const
{
    if (object.getType() == lisp::ObjectType::List)
    {
        // TODO: Error handling
        const auto& arguments_list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
        const auto first_argument = arguments_list.getContent()[0];
        const auto as_list = dynamic_cast<lisp::typesystem::ListObject&>(first_argument.getRawObject()).getContent();
        std::vector<lisp::ObjectStorage> tail(++as_list.begin(), as_list.end());
        return lisp::ObjectStorage(std::unique_ptr<lisp::IObject>(new lisp::typesystem::ListObject(tail)));
    }
    throw;
}

lisp::ObjectStorage QuoteEvaluator::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const
{
    auto arguments_list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
    return lisp::ObjectStorage(arguments_list.getContent()[0]);
}
}  // namespace nastya::builtins::lists
