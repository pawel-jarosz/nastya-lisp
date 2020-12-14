//
// Created by caedus on 12.12.2020.
//

#pragma once

#include "LispExpression/TypeSystem/GenericObject.hpp"

#include <string>

namespace nastya::lisp::typesystem {
class StringObject : public GenericObject {
public:
    StringObject(std::string value);
    std::string getValue() const;
    IObject* clone() const override;
private:
    std::string m_value;
};
}
