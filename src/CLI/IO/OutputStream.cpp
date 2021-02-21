//
// Created by caedus on 06.01.2021.
//

#include "CLI/IO/OutputStream.hpp"

namespace nastya::cli::io::stdio {

OutputStream::OutputStream(std::ostream& stream) : m_stream{stream}
{
}

void OutputStream::writeLine(std::string line)
{
    m_stream << line << "\n";
}

void OutputStream::write(std::string line)
{
    m_stream << line;
}

}  // namespace nastya::cli::io::stdio
