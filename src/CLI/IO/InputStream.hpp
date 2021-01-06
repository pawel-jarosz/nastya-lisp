//
// Created by caedus on 06.01.2021.
//

#pragma once

#include "CLI/Interface/IInputSource.hpp"

#include <istream>

namespace nastya::cli::io::stdio {

class InputStream : public IInputSource {
public:
    InputStream(std::istream& stream);
    std::string readLine() override;
private:
    std::istream& m_stream;
};

}
