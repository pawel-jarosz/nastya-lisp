//
// Created by caedus on 06.01.2021.
//

#pragma once

#include "CLI/Interface/IIoFactory.hpp"

#include <istream>
#include <ostream>

namespace nastya::cli::io::stdio {

class StreamWrapperFactory : public IIoFactory {
public:
    StreamWrapperFactory(std::istream& input, std::ostream& output);
    But::NotNullUnique<IInputSource> create_input() override;
    But::NotNullUnique<IOutputSink> create_output() override;
private:
    std::istream& m_input;
    std::ostream& m_output;
};

}
