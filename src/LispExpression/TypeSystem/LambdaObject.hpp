//
// Created by caedus on 17.01.2021.
//

#pragma once

#include "LispExpression/TypeSystem/ListObject.hpp"

namespace nastya::lisp::typesystem {

class LambdaObject : public IObject {
public:
    // TODO: Add returning primitives case
    LambdaObject(const ListObject& argumentsList, const ListObject& command);
    LambdaObject(const LambdaObject& rhs);
    LambdaObject(LambdaObject&& rhs);
    LambdaObject& operator=(const LambdaObject& rhs);
    LambdaObject& operator=(LambdaObject&& rhs);

    ObjectType getType() const override;
    IObject* clone() const override;
    std::string toString() const override;
    std::string info() const override;

    const ListObject& getArgumentsList() const;
    const ListObject& getCommand() const;

private:
    ListObject m_arguments;
    ListObject m_command;
};

}
