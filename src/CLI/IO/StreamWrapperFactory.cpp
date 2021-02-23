//
// Created by caedus on 06.01.2021.
//

#include "CLI/IO/InputStream.hpp"
#include "CLI/IO/OutputStream.hpp"
#include "CLI/IO/StreamWrapperFactory.hpp"

namespace nastya::cli::io::stdio {

StreamWrapperFactory::StreamWrapperFactory(std::istream& input, std::ostream& output) : m_input{input}, m_output{output}
{
}

But::NotNullUnique<IInputSource> StreamWrapperFactory::create_input()
{
    auto input = std::make_unique<InputStream>(m_input);
    return But::NotNullUnique<IInputSource>(input.release());
}

But::NotNullUnique<IOutputSink> StreamWrapperFactory::create_output()
{
    auto output = std::make_unique<OutputStream>(m_output);
    return But::NotNullUnique<IOutputSink>(output.release());
}

}  // namespace nastya::cli::io::stdio
