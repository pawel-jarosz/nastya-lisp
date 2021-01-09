#pragma once

#include "LispExpression/Interface/IObject.hpp"
#include "LispExpression/TypeSystem/EqualTrait.hpp"

namespace nastya::lisp::typesystem {

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

}  // namespace nastya::lisp::typesystem
