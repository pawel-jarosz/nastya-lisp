#pragma once

#include "EqualTrait.hpp"
#include "TypeSystem/Interface/IObject.hpp"

namespace nastya::typesystem {

class GenericObject : public IObject, public HasEqualTrait
{
public:
    ObjectType getType() const override;
    bool equal(const IObject& object) const override;
protected:
    explicit GenericObject(ObjectType type);

private:
    ObjectType m_type;
};

}  // namespace nastya::typesystem
