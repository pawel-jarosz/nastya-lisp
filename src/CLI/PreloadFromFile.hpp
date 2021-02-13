//
// Created by caedus on 30.01.2021.
//

#include "LispExpression/Interface/IExpressionBuilder.hpp"
#include "Runtime/Interface/IMachine.hpp"
#include "Tokenizer/Interface/ITokenizer.hpp"

namespace nastya::cli {

class PreloadFromFile {
public:
    PreloadFromFile(parser::ITokenizer& parser, lisp::IExpressionBuilder& expressionBuilder, runtime::IMachine& machine);
    void loadFile(const std::string& file_name);
private:
    parser::ITokenizer& m_parser;
    lisp::IExpressionBuilder& m_expressionBuilder;
    runtime::IMachine& m_machine;
};

}