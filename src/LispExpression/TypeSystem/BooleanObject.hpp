//
// Created by caedus on 12.12.2020.
//

#pragma once

#include "LispExpression/TypeSystem/GenericObject.hpp"

namespace nastya::lisp::typesystem {
class BooleanObject : public GenericObject {
public:
    BooleanObject(bool value);
    bool getValue() const;
    IObject* clone() const override;
    std::string toString() const override;
private:
    bool m_value;
};
}
