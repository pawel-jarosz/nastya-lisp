//
// Created by caedus on 10.01.2021.
//

#include "Utilities/LispCast.hpp"
#include "Utilities/LispCastException.hpp"

namespace nastya::utils {

template<typename T>
struct TypeToEnum {
};

template<>
struct TypeToEnum<lisp::typesystem::NumberObject> {
    constexpr static lisp::ObjectType type = lisp::ObjectType::Number;
};

template<>
struct TypeToEnum<lisp::typesystem::ListObject> {
    constexpr static lisp::ObjectType type = lisp::ObjectType::List;
};

template<>
struct TypeToEnum<lisp::typesystem::StringObject> {
    constexpr static lisp::ObjectType type = lisp::ObjectType::String;
};

template<>
struct TypeToEnum<lisp::typesystem::LabelObject> {
    constexpr static lisp::ObjectType type = lisp::ObjectType::Label;
};

template<>
struct TypeToEnum<lisp::typesystem::BooleanObject> {
    constexpr static lisp::ObjectType type = lisp::ObjectType::Boolean;
};

template<typename Target>
const Target& cast(const lisp::ObjectStorage& storage, const std::string& msg) {
    if(storage.getType() == TypeToEnum<Target>::type) {
        return dynamic_cast<const Target&>(storage.getRawObject());
    }
    BUT_THROW(LispCastException, msg);
}

const lisp::typesystem::BooleanObject& Cast::as_boolean(const lisp::ObjectStorage& storage, std::string msg)
{
    return cast<lisp::typesystem::BooleanObject>(storage, msg);
}
const lisp::typesystem::NumberObject& Cast::as_number(const lisp::ObjectStorage& storage, std::string msg)
{
    return cast<lisp::typesystem::NumberObject>(storage, msg);
}
const lisp::typesystem::StringObject& Cast::as_string(const lisp::ObjectStorage& storage, std::string msg)
{
    return cast<lisp::typesystem::StringObject>(storage, msg);
}
const lisp::typesystem::LabelObject& Cast::as_label(const lisp::ObjectStorage& storage, std::string msg)
{
    return cast<lisp::typesystem::LabelObject>(storage, msg);
}
const lisp::typesystem::ListObject& Cast::as_list(const lisp::ObjectStorage& storage, std::string msg)
{
    return cast<lisp::typesystem::ListObject>(storage, msg);
}
}
