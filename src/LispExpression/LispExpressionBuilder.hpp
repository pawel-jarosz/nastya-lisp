//
// Created by caedus on 15.12.2020.
//

#pragma once

#include "LispExpression/Interface/IExpressionBuilder.hpp"
#include "LispExpression/Interface/IObjectFactory.hpp"
#include "Parser/Interface/IParser.hpp"
#include "LispExpression/ObjectStorage.hpp"

#include <memory>

namespace nastya::lisp {

class LispExpressionBuilder : public IExpressionBuilder {
public:
    explicit LispExpressionBuilder(parser::IParser& parser, IObjectFactory& object_factory);
    ~LispExpressionBuilder() override;
    ObjectStorage build() override;
private:
    class LispExpressionBuilderImpl;
    parser::IParser& m_parser;
    IObjectFactory& m_object_factory;
    std::unique_ptr<LispExpressionBuilderImpl> m_impl;
};
}