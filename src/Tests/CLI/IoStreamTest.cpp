//
// Created by caedus on 06.01.2021.
//

#include <sstream>

#include <gtest/gtest.h>

#include "CLI/IO/StreamWrapperFactory.hpp"

namespace nastya::cli::io {

using namespace ::testing;

struct IoStreamTest : public Test
{
    IoStreamTest() : input_stream(), output_stream(), factory(input_stream, output_stream)
    {
    }
    std::stringstream input_stream, output_stream;
    stdio::StreamWrapperFactory factory;
};

TEST_F(IoStreamTest, testInputStream)
{
    auto input = factory.create_input();
    std::string test_case{"Hello world"};
    input_stream << test_case << "\n";
    auto result = input->readLine();
    EXPECT_EQ(result, test_case);
}

TEST_F(IoStreamTest, testOutputStream)
{
    auto output = factory.create_output();
    std::string test_case{"Hello world"};
    output->writeLine(test_case);
    std::string result;
    getline(output_stream, result);
    EXPECT_EQ(test_case, result);
    std::string test_case2{"But only line\n"};
    output->write(test_case2);
    getline(output_stream, result);
    EXPECT_EQ(std::string(test_case2.begin(), --test_case2.end()), result);
}

}  // namespace nastya::cli::io