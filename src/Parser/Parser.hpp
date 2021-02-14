//
// Created by caedus on 15.12.2020.
//

#pragma once

#include <memory>

#include "Parser/Interface/IObjectFactory.hpp"
#include "Parser/Interface/IParser.hpp"
#include "Tokenizer/Interface/ITokenizer.hpp"
#include "TypeSystem/ObjectStorage.hpp"

namespace nastya::lisp {

struct ParserImpl;

class Parser : public IParser
{
public:
    explicit Parser(tokens::ITokenizer& parser, IObjectFactory& object_factory);
    ~Parser() override;
    typesystem::ObjectStorage build() override;
    void reset() override;

private:
    tokens::ITokenizer& m_parser;
    IObjectFactory& m_object_factory;
    std::unique_ptr<ParserImpl> m_impl;
};
}  // namespace nastya::lisp