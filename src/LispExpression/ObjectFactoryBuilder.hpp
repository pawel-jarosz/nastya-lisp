#pragma once

#include "LispExpression/Interface/IObjectFactory.hpp"

namespace nastya::lisp {

class ObjectFactoryBuilder {
public:
    ObjectFactoryBuilder(IObjectFactory& factory);
    void build();
private:
    IObjectFactory& m_factory;
};

}