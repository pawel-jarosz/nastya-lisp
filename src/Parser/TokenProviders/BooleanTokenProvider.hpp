//
// Created by caedus on 09.02.2021.
//

#include <memory>
#include <optional>

#include "Parser/Interface/ITokenProvider.hpp"

namespace nastya::parser {

const std::string TRUE_VALUE = "#true";
const std::string FALSE_VALUE = "#false";

class BooleanTokenProvider : public ITokenProvider
{
public:
    BooleanTokenProvider(std::string true_string, std::string false_string);
    std::optional<Token> getTokenIfAvailable(const std::string& value, ParsingContext& context) const override;
    static std::unique_ptr<ITokenProvider> create();
private:
    std::string m_true_value;
    std::string m_false_value;
};

}
