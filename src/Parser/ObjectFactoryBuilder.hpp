#pragma once

#include "Parser/Interface/IObjectFactory.hpp"

namespace nastya::parser {

class ObjectFactoryBuilder
{
public:
    ObjectFactoryBuilder(IObjectFactory& factory);
    void build();

private:
    IObjectFactory& m_factory;
};

}  // namespace nastya::parser