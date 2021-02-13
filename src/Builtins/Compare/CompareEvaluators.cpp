//
// Created by caedus on 06.01.2021.
//

#include "Builtins/Compare/CompareEvaluators.hpp"

#include "TypeSystem/Types/BooleanObject.hpp"
#include "TypeSystem/Types/NumberObject.hpp"
#include "TypeSystem/Types/ListObject.hpp"
#include "Builtins/BuiltinsException.hpp"

namespace nastya::builtins::compare {

int compare(const lisp::ObjectStorage& a, const lisp::ObjectStorage& b) {
    const auto& a_is_comparable = dynamic_cast<lisp::typesystem::HasComparableTrait&>(a.getRawObject())
                               .isComparable();
    if (not a_is_comparable) {
        BUT_THROW(BuiltinsException, "One or both types are not comparable");
    }
    auto& comparable_a = dynamic_cast<lisp::typesystem::ComparableObject&>(a.getRawObject());
    return comparable_a.compare(b.getRawObject());
}

lisp::typesystem::BooleanObject* equal(const lisp::ObjectStorage& a, const lisp::ObjectStorage& b) {
    const auto& as_generic = dynamic_cast<lisp::typesystem::GenericObject&>(a.getRawObject());
    return new lisp::typesystem::BooleanObject(as_generic.equal(b.getRawObject()));
}

lisp::ObjectStorage EqualEvaluator::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const {
    if (object.getType() != lisp::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.Equal expects list of arguments");
    }
    const auto& arguments_list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 2) {
        BUT_THROW(BuiltinsException, "Lang.Compare.Equal expects exactly two argument");
    }
    const auto& first_argument = arguments_list.getContent()[0];
    const auto& second_argument = arguments_list.getContent()[1];
    auto returned_object = std::unique_ptr<lisp::IObject>(equal(first_argument, second_argument));
    return lisp::ObjectStorage(std::move(returned_object));}

lisp::ObjectStorage CompareEvaluator::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const {
    if (object.getType() != lisp::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.Compare expects list of arguments");
    }
    const auto& arguments_list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 2) {
        BUT_THROW(BuiltinsException, "Lang.Compare.Compare expects exactly two argument");
    }
    const auto& first_argument = arguments_list.getContent()[0];
    const auto& second_argument = arguments_list.getContent()[1];
    auto ret_code = compare(first_argument, second_argument);
    auto returned_object = std::unique_ptr<lisp::IObject>(new lisp::typesystem::NumberObject(ret_code));
    return lisp::ObjectStorage(std::move(returned_object));
}

lisp::ObjectStorage LowerEvaluator::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const {
    if (object.getType() != lisp::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.LowerEvaluator expects list of arguments");
    }
    const auto& arguments_list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 2) {
        BUT_THROW(BuiltinsException, "Lang.Compare.LowerEvaluator expects exactly two argument");
    }
    const auto& first_argument = arguments_list.getContent()[0];
    const auto& second_argument = arguments_list.getContent()[1];
    auto ret_code = compare(first_argument, second_argument) == -1;
    auto returned_object = std::unique_ptr<lisp::IObject>(new lisp::typesystem::BooleanObject(ret_code));
    return lisp::ObjectStorage(std::move(returned_object));
}

lisp::ObjectStorage LowerOrEqualEvaluator::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const {
    if (object.getType() != lisp::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.LowerOrEqual Evaluator expects list of arguments");
    }
    const auto& arguments_list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 2) {
        BUT_THROW(BuiltinsException, "Lang.Compare.LowerOrEqualEvaluator expects exactly two argument");
    }
    const auto& first_argument = arguments_list.getContent()[0];
    const auto& second_argument = arguments_list.getContent()[1];
    int value = compare(first_argument, second_argument);
    auto ret_code = (value == -1 or value == 0);
    auto returned_object = std::unique_ptr<lisp::IObject>(new lisp::typesystem::BooleanObject(ret_code));
    return lisp::ObjectStorage(std::move(returned_object));
}

lisp::ObjectStorage GreaterOrEqualEvaluator::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const {
    if (object.getType() != lisp::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.GreaterOrEqual Evaluator expects list of arguments");
    }
    const auto& arguments_list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 2) {
        BUT_THROW(BuiltinsException, "Lang.Compare.GreaterOrEqualEvaluator expects exactly two argument");
    }
    const auto& first_argument = arguments_list.getContent()[0];
    const auto& second_argument = arguments_list.getContent()[1];
    int value = compare(first_argument, second_argument);
    auto ret_code = (value == 1 or value == 0);
    auto returned_object = std::unique_ptr<lisp::IObject>(new lisp::typesystem::BooleanObject(ret_code));
    return lisp::ObjectStorage(std::move(returned_object));
}

lisp::ObjectStorage GreaterEvaluator::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const {
    if (object.getType() != lisp::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.Greater Evaluator expects list of arguments");
    }
    const auto& arguments_list = dynamic_cast<lisp::typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 2) {
        BUT_THROW(BuiltinsException, "Lang.Compare.Greater Evaluator expects exactly two argument");
    }
    const auto& first_argument = arguments_list.getContent()[0];
    const auto& second_argument = arguments_list.getContent()[1];
    int value = compare(first_argument, second_argument);
    auto ret_code =  (value == 1);
    auto returned_object = std::unique_ptr<lisp::IObject>(new lisp::typesystem::BooleanObject(ret_code));
    return lisp::ObjectStorage(std::move(returned_object));
}

}
