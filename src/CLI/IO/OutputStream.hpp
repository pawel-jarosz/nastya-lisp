//
// Created by caedus on 06.01.2021.
//

#pragma once

#include "CLI/Interface/IOutputSink.hpp"

#include <ostream>

namespace nastya::cli::io::stdio {

class OutputStream : public IOutputSink {
public:
    OutputStream(std::ostream& stream);
    void writeLine(std::string line);
    void write(std::string line);
private:
    std::ostream& m_stream;
};

}
