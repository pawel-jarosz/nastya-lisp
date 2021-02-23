//
// Created by caedus on 30.01.2021.
//

#include "Parser/Interface/IParser.hpp"
#include "Runtime/Interface/IMachine.hpp"
#include "Tokenizer/Interface/ITokenizer.hpp"

namespace nastya::cli {

class PreloadFromFile {
public:
    PreloadFromFile(tokens::ITokenizer& parser, parser::IParser& expressionBuilder, runtime::IMachine& machine);
    void loadFile(const std::string& file_name);
private:
    tokens::ITokenizer& m_parser;
    parser::IParser& m_expressionBuilder;
    runtime::IMachine& m_machine;
};

}