//
// Created by caedus on 09.01.2021.
//

#include <algorithm>

#include "Builtins/BuiltinsException.hpp"
#include "LispExpression/TypeSystem/BooleanObject.hpp"
#include "LispExpression/TypeSystem/LambdaObject.hpp"
#include "LispExpression/TypeSystem/ListObject.hpp"
#include "SyntaxEvaluators.hpp"
#include "Utilities/LispCast.hpp"

namespace nastya::builtins::syntax {
lisp::ObjectStorage IfEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const
{
    if (object.getType() != lisp::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Syntax.If expects list of arguments");
    }
    const auto& arguments_list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 3) {
        BUT_THROW(BuiltinsException, "Lang.Syntax.If expects exactly three argument");
    }
    const auto as_list = arguments_list.getContent();
    const auto first_argument = as_list[0];
    if (first_argument.getType() != lisp::ObjectType::Boolean) {
        BUT_THROW(BuiltinsException, "Lang.Syntax.If expects exactly boolean as first argument");
    }
    const auto& boolean = dynamic_cast<const lisp::typesystem::BooleanObject&>(first_argument.getRawObject());
    return as_list[1];
}

lisp::ObjectStorage CondEvaluator::evaluate(runtime::IMemory&, const lisp::ObjectStorage& object) const
{
    if (object.getType() != lisp::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Syntax.Cond expects list of arguments");
    }
    const auto& arguments_list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.isEmpty()) {
        BUT_THROW(BuiltinsException, "Lang.Syntax.Cond unspecified return value");
    }
    const auto as_list = arguments_list.getContent();
    for (const auto& item: as_list) {
        if (item.getType() != lisp::ObjectType::List) {
            BUT_THROW(BuiltinsException, "Lang.Syntax.Cond expected list value");
        }
        const auto& list = dynamic_cast<lisp::typesystem::ListObject&>(item.getRawObject());
        const auto& condition = list.getContent();
        if (list.getSize() != 2) {
            BUT_THROW(BuiltinsException, "Lang.Syntax.Cond Invalid condition format");
        }
        if (condition[0].getType() == lisp::ObjectType::Boolean)
        {
            const auto& boolean = dynamic_cast<lisp::typesystem::BooleanObject&>(condition[0].getRawObject());
            if (boolean.getValue())
            {
                return condition[1];
            }
            else {
                continue;
            }
        }
        if (condition[0].getType() == lisp::ObjectType::Label and condition[0].toString() == "Else") {
            return condition[1];
        }
        BUT_THROW(BuiltinsException, "Lang.Syntax.Cond Invalid type");
    }
    BUT_THROW(BuiltinsException, "Lang.Syntax.Cond unspecified return value");
}

lisp::ObjectStorage DefineEvaluator::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const
{
    const auto& list = utils::Cast::as_list(object, "Lang.Syntax.Define expects list of arguments").getContent();
    const auto variable_name = utils::Cast::as_label(list[0], "Lang.Syntax.Define expects label");
    const auto variable_value = list[1];
    memory.registerVariableOnHeap(variable_name, variable_value);
    return list[0];
}

lisp::ObjectStorage LetInEvaluator::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const
{
    return object;
}

lisp::ObjectStorage LambdaEvaluator::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const
{
    const auto& arguments = utils::Cast::as_list(object, "Lang.Syntax.Lambda expects list of arguments")
                                .getContent();
    const auto& list_of_arguments = utils::Cast::as_list(arguments[0],
                                                         "Lang.Syntax.Lambda expects list of as an arguments list");
    std::for_each(list_of_arguments.getContent().begin(), list_of_arguments.getContent().end(),
                  [](const auto& label) {
                      utils::Cast::as_label(label, "Lang.Syntax.Lambda expects only labels on argument list");
                  });
    const auto& function = utils::Cast::as_list(arguments[1], "Lang.Syntax.Lambda expects list as a command");
    std::unique_ptr<lisp::IObject> lambda(new lisp::typesystem::LambdaObject(list_of_arguments, function));
    return lisp::ObjectStorage(std::move(lambda));
}

}  // namespace nastya::builtins::syntax
