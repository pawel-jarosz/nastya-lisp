#include <Tokenizer/Types/Token.hpp>

namespace nastya::tokens {

Token create_boolean_token(bool value);
Token create_integer_token(int value);
Token create_floating_token(float value);
Token create_label_token(std::string value);
Token create_string_token(std::string value);

template <typename GivenValue, typename ExpectedValue>
struct TestCase
{
    GivenValue first;
    ExpectedValue second;
};

}
