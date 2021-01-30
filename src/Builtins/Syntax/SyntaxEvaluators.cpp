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
    return as_list[boolean.getValue() ? 1 : 2];
}

lisp::ObjectStorage IfEvaluator::preExecute(const lisp::typesystem::ListObject& object, runtime::IMachine& vm) const
{
    const auto content = object.getContent();
    std::vector<lisp::ObjectStorage> arguments;
    arguments.emplace_back(vm.run(content[1]));
    const auto& boolean = utils::Cast::as_boolean(arguments[0], "Value should be computed to boolean");
    if (boolean.getValue()) {
        arguments.emplace_back(vm.run(content[2]));
        arguments.emplace_back(lisp::ObjectStorage(std::unique_ptr<lisp::IObject>(new lisp::typesystem::ListObject())));
    }
    else {
        arguments.emplace_back(lisp::ObjectStorage(std::unique_ptr<lisp::IObject>(new lisp::typesystem::ListObject())));
        arguments.emplace_back(vm.run(content[3]));
    }
    std::unique_ptr<lisp::IObject> obj(new lisp::typesystem::ListObject(arguments));
    lisp::ObjectStorage result(std::move(obj));
    return result;
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

lisp::ObjectStorage CondEvaluator::preExecute(const lisp::typesystem::ListObject& object, runtime::IMachine& vm) const
{
    const auto content = object.getContent();
    std::vector conditions(++content.begin(), content.end());
    std::vector<lisp::ObjectStorage> arguments;

    for (const auto& condition: conditions) {
        const auto& condition_tuple_list = utils::Cast::as_list(condition);
        const auto condition_tuple = condition_tuple_list.getContent();
        const auto bool_expression = condition_tuple[0];
        const auto expected_value = condition_tuple[1];
        const auto evaluated_bool = vm.run(bool_expression);
        const auto evaluated_value = vm.run(expected_value);
        std::vector<lisp::ObjectStorage> result{evaluated_bool, evaluated_value};
        std::unique_ptr<lisp::IObject> result_as_list(new lisp::typesystem::ListObject(result));
        nastya::lisp::ObjectStorage prepared_condition(std::move(result_as_list));
        arguments.emplace_back(std::move(prepared_condition));
    }

    std::unique_ptr<lisp::IObject> obj(new lisp::typesystem::ListObject(arguments));
    lisp::ObjectStorage result(std::move(obj));
    return result;
}

lisp::ObjectStorage DefineEvaluator::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const
{
    const auto& list = utils::Cast::as_list(object, "Lang.Syntax.Define expects list of arguments").getContent();
    const auto variable_name = utils::Cast::as_label(list[0], "Lang.Syntax.Define expects label");
    const auto variable_value = list[1];
    memory.registerVariableOnHeap(variable_name, variable_value);
    return list[0];
}

lisp::ObjectStorage DefineEvaluator::preExecute(const lisp::typesystem::ListObject& object, runtime::IMachine& vm) const
{
    const auto content = object.getContent();
    // TODO: Add exception for invalid list of argument
    const auto variable_name = content[1];
    const auto variable_value = vm.run(content[2]);
    std::vector<lisp::ObjectStorage> arguments = { variable_name, variable_value };
    std::unique_ptr<lisp::IObject> obj(new lisp::typesystem::ListObject(arguments));
    lisp::ObjectStorage result(std::move(obj));
    return result;
}

lisp::ObjectStorage LetInEvaluator::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const
{
    return object;
}

bool isInLabel(const lisp::ObjectStorage& object) {
    if (object.getType() != lisp::ObjectType::Label) {
        return false;
    }
    const auto& label = utils::Cast::as_label(object);
    return (label.getValue() == "In");
}

lisp::ObjectStorage LetInEvaluator::preExecute(const lisp::typesystem::ListObject& object, runtime::IMachine& vm) const
{
    // TODO: Exception handling
    const auto& content = object.getContent();
    const auto end_of_variable_definitions = std::find_if(content.begin() + 1, content.end(), isInLabel);
    auto it = content.begin() + 1;
    while(it != end_of_variable_definitions) {
        const auto& tuple = utils::Cast::as_list(*it);
        const auto& variable_name = utils::Cast::as_label(tuple.getContent()[0]);
        const auto& variable_value = vm.run(tuple.getContent()[1]);
        vm.pushStackFrame();
        vm.registerVariableOnStack(variable_name, variable_value);
        ++it;
    }
    const auto expression = end_of_variable_definitions + 1;
    const auto result = vm.run(*expression);
    vm.popStackFrame();
    return result;
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

lisp::ObjectStorage LambdaEvaluator::preExecute(const lisp::typesystem::ListObject& object, runtime::IMachine& vm) const
{
    const auto& content = object.getContent();
    std::vector arguments(content.begin() + 1, content.end());
    // check if only two arguments
    std::unique_ptr<lisp::IObject> result(new lisp::typesystem::ListObject(arguments));
    return lisp::ObjectStorage(std::move(result));
}

}  // namespace nastya::builtins::syntax
