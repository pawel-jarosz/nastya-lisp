//
// Created by caedus on 09.01.2021.
//

#include <LispExpression/TypeSystem/BooleanObject.hpp>
#include "LispExpression/TypeSystem/ListObject.hpp"
#include "Builtins/BuiltinsException.hpp"
#include "SyntaxEvaluators.hpp"

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
    if (boolean.getValue()) {
        return as_list[1];
    }
    return as_list[2];
}

}  // namespace nastya::builtins::syntax
