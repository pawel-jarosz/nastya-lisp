//
// Created by caedus on 10.01.2021.
//

#include "VirtualMachine/ArgumentPreparationStrategy/DefaultStrategy.hpp"
#include "VirtualMachine/ArgumentPreparationStrategy/QuoteStrategy.hpp"
#include "VirtualMachine/ArgumentPreparationStrategy/CondStrategy.hpp"

#include "Utilities/LispCast.hpp"

#include <algorithm>

namespace nastya::vm {

lisp::ObjectStorage DefaultStrategy::extract_arguments(const lisp::typesystem::ListObject& object, vm::IMachine& vm) const
{
    const auto content = object.getContent();
    std::vector<lisp::ObjectStorage> arguments;
    std::for_each(++content.begin(), content.end(), [&](const auto& obj) { arguments.emplace_back(vm.run(obj)); });
    std::unique_ptr<lisp::IObject> obj(new lisp::typesystem::ListObject(arguments));
    lisp::ObjectStorage result(std::move(obj));
    return result;
}

lisp::ObjectStorage QuoteStrategy::extract_arguments(const lisp::typesystem::ListObject& object, vm::IMachine& vm) const
{
    const auto content = object.getContent();
    std::vector<lisp::ObjectStorage> arguments(++content.begin(), content.end());
    std::unique_ptr<lisp::IObject> obj(new lisp::typesystem::ListObject(arguments));
    lisp::ObjectStorage result(std::move(obj));
    return result;
}

lisp::ObjectStorage CondStrategy::extract_arguments(const lisp::typesystem::ListObject& object, vm::IMachine& vm) const
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

}
