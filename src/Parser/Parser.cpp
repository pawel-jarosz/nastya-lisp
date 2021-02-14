//
// Created by caedus on 15.12.2020.
//

#include <vector>

#include "Parser/Internal/ParserImpl.hpp"
#include "Parser/Parser.hpp"

namespace nastya::lisp {

Parser::Parser(tokens::ITokenizer& parser, IObjectFactory& object_factory)
: m_parser{parser}
, m_object_factory{object_factory}
, m_impl(new ParserImpl(object_factory))
{
}

Parser::~Parser()
{
}

typesystem::ObjectStorage Parser::build()
{
    tokens::Token t;
    while ((t = m_parser.getToken()).type != tokens::TokenType::Eof)
    {
        m_impl->addToken(t);
    }
    return m_impl->build();
}
void Parser::reset()
{
    m_impl.reset(new ParserImpl(m_object_factory));
}

}  // namespace nastya::lisp
