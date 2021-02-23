//
// Created by caedus on 10.01.2021.
//

#include "Utilities/LispCast.hpp"
#include "Utilities/LispCastException.hpp"

namespace nastya::utils {

template <typename T>
struct TypeToEnum
{
};

template <>
struct TypeToEnum<typesystem::NumberObject>
{
    constexpr static typesystem::ObjectType type = typesystem::ObjectType::Number;
};

template <>
struct TypeToEnum<typesystem::ListObject>
{
    constexpr static typesystem::ObjectType type = typesystem::ObjectType::List;
};

template <>
struct TypeToEnum<typesystem::StringObject>
{
    constexpr static typesystem::ObjectType type = typesystem::ObjectType::String;
};

template <>
struct TypeToEnum<typesystem::LabelObject>
{
    constexpr static typesystem::ObjectType type = typesystem::ObjectType::Label;
};

template <>
struct TypeToEnum<typesystem::BooleanObject>
{
    constexpr static typesystem::ObjectType type = typesystem::ObjectType::Boolean;
};

template <>
struct TypeToEnum<typesystem::LambdaObject>
{
    constexpr static typesystem::ObjectType type = typesystem::ObjectType::Lambda;
};

template <typename Target>
const Target& cast(const typesystem::ObjectStorage& storage, const std::string& msg)
{
    if (storage.getType() == TypeToEnum<Target>::type)
    {
        return dynamic_cast<const Target&>(storage.getRawObject());
    }
    BUT_THROW(LispCastException, msg);
}

const typesystem::BooleanObject& Cast::as_boolean(const typesystem::ObjectStorage& storage, std::string msg)
{
    return cast<typesystem::BooleanObject>(storage, msg);
}

const typesystem::NumberObject& Cast::as_number(const typesystem::ObjectStorage& storage, std::string msg)
{
    return cast<typesystem::NumberObject>(storage, msg);
}
const typesystem::StringObject& Cast::as_string(const typesystem::ObjectStorage& storage, std::string msg)
{
    return cast<typesystem::StringObject>(storage, msg);
}
const typesystem::LabelObject& Cast::as_label(const typesystem::ObjectStorage& storage, std::string msg)
{
    return cast<typesystem::LabelObject>(storage, msg);
}

const typesystem::ListObject& Cast::as_list(const typesystem::ObjectStorage& storage, std::string msg)
{
    return cast<typesystem::ListObject>(storage, msg);
}

const typesystem::LambdaObject& Cast::as_lambda(const typesystem::ObjectStorage& storage, std::string msg)
{
    return cast<typesystem::LambdaObject>(storage, msg);
}
}  // namespace nastya::utils
