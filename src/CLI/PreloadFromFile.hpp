//
// Created by caedus on 30.01.2021.
//

#include "Parser/Interface/IParser.hpp"
#include "LispExpression/Interface/IExpressionBuilder.hpp"
#include "Runtime/Interface/IMachine.hpp"

namespace nastya::cli {

class PreloadFromFile {
public:
    PreloadFromFile(parser::IParser& parser, lisp::IExpressionBuilder& expressionBuilder, runtime::IMachine& machine);
    void loadFile(const std::string& file_name);
private:
    parser::IParser& m_parser;
    lisp::IExpressionBuilder& m_expressionBuilder;
    runtime::IMachine& m_machine;
};

}