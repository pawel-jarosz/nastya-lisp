#pragma once

#include "Parser/Interface/IObjectFactory.hpp"

namespace nastya::lisp {

class ObjectFactoryBuilder
{
public:
    ObjectFactoryBuilder(IObjectFactory& factory);
    void build();

private:
    IObjectFactory& m_factory;
};

}  // namespace nastya::lisp