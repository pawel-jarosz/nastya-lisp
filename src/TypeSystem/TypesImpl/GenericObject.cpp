#include <sstream>
#include <utility>

#include "TypeSystem/Types/GenericObject.hpp"
#include "TypeSystem/Types/LambdaObject.hpp"
#include "TypeSystem/Types/ListObject.hpp"

namespace nastya::lisp::typesystem {

template <typename T>
std::string toString(const T& value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

GenericObject::GenericObject(ObjectType type) : m_type{type}
{
}

ObjectType GenericObject::getType() const
{
    return m_type;
}
bool GenericObject::equal(const IObject& object) const
{
    return (toString() == object.toString());
}


}  // namespace nastya::lisp::typesystem
