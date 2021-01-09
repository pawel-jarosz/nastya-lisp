//
// Created by caedus on 06.01.2021.
//

#include "Builtins/Compare/CompareEvaluators.hpp"

#include "LispExpression/TypeSystem/BooleanObject.hpp"
#include "LispExpression/TypeSystem/NumberObject.hpp"
#include "LispExpression/TypeSystem/ListObject.hpp"
#include "Builtins/BuiltinsException.hpp"

namespace nastya::builtins::compare {

lisp::typesystem::NumberObject* compare(const lisp::ObjectStorage& a, const lisp::ObjectStorage& b) {
    const auto& a_is_comparable = dynamic_cast<lisp::typesystem::HasComparableTrait&>(a.getRawObject())
                               .isComparable();
    if (not a_is_comparable) {
        BUT_THROW(BuiltinsException, "One or both types are not comparable");
    }
    auto& comparable_a = dynamic_cast<lisp::typesystem::ComparableObject&>(a.getRawObject());
    return new lisp::typesystem::NumberObject(comparable_a.compare(b.getRawObject()));
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
    auto returned_object = std::unique_ptr<lisp::IObject>(compare(first_argument, second_argument));
    return lisp::ObjectStorage(std::move(returned_object));
}

}
