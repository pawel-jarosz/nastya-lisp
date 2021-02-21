//
// Created by caedus on 30.01.2021.
//

#include <fstream>

#include "CLI/PreloadFromFile.hpp"

namespace nastya::cli {

PreloadFromFile::PreloadFromFile(tokens::ITokenizer& parser,
                                 parser::IParser& expressionBuilder,
                                 runtime::IMachine& machine)
: m_parser{parser}, m_expressionBuilder{expressionBuilder}, m_machine{machine}
{
}

void PreloadFromFile::loadFile(const std::string& file_name)
{
    std::fstream in(file_name);
    std::string line;

    while (std::getline(in, line))
    {
        m_parser.reset(line);
        auto expression = m_expressionBuilder.build();
        m_machine.run(expression);
        m_expressionBuilder.reset();
    }
}
}  // namespace nastya::cli
