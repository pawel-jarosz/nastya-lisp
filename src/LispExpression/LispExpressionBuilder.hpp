//
// Created by caedus on 15.12.2020.
//

#pragma once

#include <memory>

#include "LispExpression/Interface/IExpressionBuilder.hpp"
#include "LispExpression/Interface/IObjectFactory.hpp"
#include "Tokenizer/Interface/ITokenizer.hpp"
#include "TypeSystem/ObjectStorage.hpp"

namespace nastya::lisp {

class LispExpressionBuilder : public IExpressionBuilder
{
public:
    explicit LispExpressionBuilder(parser::ITokenizer& parser, IObjectFactory& object_factory);
    ~LispExpressionBuilder() override;
    ObjectStorage build() override;
    void reset() override;

private:
    class LispExpressionBuilderImpl;
    parser::ITokenizer& m_parser;
    IObjectFactory& m_object_factory;
    std::unique_ptr<LispExpressionBuilderImpl> m_impl;
};
}  // namespace nastya::lisp