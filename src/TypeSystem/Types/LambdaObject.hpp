//
// Created by caedus on 17.01.2021.
//

#pragma once

#include "ListObject.hpp"

namespace nastya::typesystem {

class LambdaObject : public IObject {
public:
    LambdaObject(const ListObject& argumentsList, const IObject& command);
    LambdaObject(const LambdaObject& rhs);
    LambdaObject(LambdaObject&& rhs);
    LambdaObject& operator=(const LambdaObject& rhs);
    LambdaObject& operator=(LambdaObject&& rhs);

    ObjectType getType() const override;
    IObject* clone() const override;
    std::string toString() const override;
    std::string info() const override;

    const ListObject& getArgumentsList() const;
    const IObject& getCommand() const;

private:
    ListObject m_arguments;
    std::unique_ptr<IObject> m_command;
};

}
