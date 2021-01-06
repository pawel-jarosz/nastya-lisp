//
// Created by caedus on 06.01.2021.
//

#include "CLI/IO/InputStream.hpp"

namespace nastya::cli::io::stdio {
InputStream::InputStream(std::istream& stream)
: m_stream{stream}
{
}

std::string InputStream::readLine()
{
    std::string result;
    getline(m_stream, result);
    return result;
}

}
