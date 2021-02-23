//
// Created by caedus on 06.01.2021.
//

#include "Builtins/BuiltinsException.hpp"
#include "Builtins/Compare/CompareEvaluators.hpp"
#include "TypeSystem/Types/BooleanObject.hpp"
#include "TypeSystem/Types/ListObject.hpp"
#include "TypeSystem/Types/NumberObject.hpp"

namespace nastya::builtins::compare {

int compare(const typesystem::ObjectStorage& a, const typesystem::ObjectStorage& b)
{
    const auto& a_is_comparable = dynamic_cast<typesystem::HasComparableTrait&>(a.getRawObject()).isComparable();
    if (not a_is_comparable)
    {
        BUT_THROW(BuiltinsException, "One or both types are not comparable");
    }
    auto& comparable_a = dynamic_cast<typesystem::ComparableObject&>(a.getRawObject());
    return comparable_a.compare(b.getRawObject());
}

typesystem::BooleanObject* equal(const typesystem::ObjectStorage& a, const typesystem::ObjectStorage& b)
{
    const auto& as_generic = dynamic_cast<typesystem::GenericObject&>(a.getRawObject());
    return new typesystem::BooleanObject(as_generic.equal(b.getRawObject()));
}

typesystem::ObjectStorage
EqualEvaluator::evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const
{
    if (object.getType() != typesystem::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.Equal expects list of arguments");
    }
    const auto& arguments_list = dynamic_cast<typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 2)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.Equal expects exactly two argument");
    }
    const auto& first_argument = arguments_list.getContent()[0];
    const auto& second_argument = arguments_list.getContent()[1];
    auto returned_object = std::unique_ptr<typesystem::IObject>(equal(first_argument, second_argument));
    return typesystem::ObjectStorage(std::move(returned_object));
}

typesystem::ObjectStorage
CompareEvaluator::evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const
{
    if (object.getType() != typesystem::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.Compare expects list of arguments");
    }
    const auto& arguments_list = dynamic_cast<typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 2)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.Compare expects exactly two argument");
    }
    const auto& first_argument = arguments_list.getContent()[0];
    const auto& second_argument = arguments_list.getContent()[1];
    auto ret_code = compare(first_argument, second_argument);
    auto returned_object = std::unique_ptr<typesystem::IObject>(new typesystem::NumberObject(ret_code));
    return typesystem::ObjectStorage(std::move(returned_object));
}

typesystem::ObjectStorage
LowerEvaluator::evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const
{
    if (object.getType() != typesystem::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.LowerEvaluator expects list of arguments");
    }
    const auto& arguments_list = dynamic_cast<typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 2)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.LowerEvaluator expects exactly two argument");
    }
    const auto& first_argument = arguments_list.getContent()[0];
    const auto& second_argument = arguments_list.getContent()[1];
    auto ret_code = compare(first_argument, second_argument) == -1;
    auto returned_object = std::unique_ptr<typesystem::IObject>(new typesystem::BooleanObject(ret_code));
    return typesystem::ObjectStorage(std::move(returned_object));
}

typesystem::ObjectStorage
LowerOrEqualEvaluator::evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const
{
    if (object.getType() != typesystem::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.LowerOrEqual Evaluator expects list of arguments");
    }
    const auto& arguments_list = dynamic_cast<typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 2)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.LowerOrEqualEvaluator expects exactly two argument");
    }
    const auto& first_argument = arguments_list.getContent()[0];
    const auto& second_argument = arguments_list.getContent()[1];
    int value = compare(first_argument, second_argument);
    auto ret_code = (value == -1 or value == 0);
    auto returned_object = std::unique_ptr<typesystem::IObject>(new typesystem::BooleanObject(ret_code));
    return typesystem::ObjectStorage(std::move(returned_object));
}

typesystem::ObjectStorage
GreaterOrEqualEvaluator::evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const
{
    if (object.getType() != typesystem::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.GreaterOrEqual Evaluator expects list of arguments");
    }
    const auto& arguments_list = dynamic_cast<typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 2)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.GreaterOrEqualEvaluator expects exactly two argument");
    }
    const auto& first_argument = arguments_list.getContent()[0];
    const auto& second_argument = arguments_list.getContent()[1];
    int value = compare(first_argument, second_argument);
    auto ret_code = (value == 1 or value == 0);
    auto returned_object = std::unique_ptr<typesystem::IObject>(new typesystem::BooleanObject(ret_code));
    return typesystem::ObjectStorage(std::move(returned_object));
}

typesystem::ObjectStorage
GreaterEvaluator::evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const
{
    if (object.getType() != typesystem::ObjectType::List)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.Greater Evaluator expects list of arguments");
    }
    const auto& arguments_list = dynamic_cast<typesystem::ListObject&>(object.getRawObject());
    if (arguments_list.getSize() != 2)
    {
        BUT_THROW(BuiltinsException, "Lang.Compare.Greater Evaluator expects exactly two argument");
    }
    const auto& first_argument = arguments_list.getContent()[0];
    const auto& second_argument = arguments_list.getContent()[1];
    int value = compare(first_argument, second_argument);
    auto ret_code = (value == 1);
    auto returned_object = std::unique_ptr<typesystem::IObject>(new typesystem::BooleanObject(ret_code));
    return typesystem::ObjectStorage(std::move(returned_object));
}

}  // namespace nastya::builtins::compare
