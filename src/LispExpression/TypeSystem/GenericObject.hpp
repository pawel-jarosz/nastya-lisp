#pragma once

#include "LispExpression/Interface/IObject.hpp"

namespace nastya::lisp::typesystem {

class GenericObject : public IObject
{
public:
    ObjectType getType() const override;

protected:
    GenericObject(ObjectType type);

private:
    ObjectType m_type;
};

}  // namespace nastya::lisp::typesystem
