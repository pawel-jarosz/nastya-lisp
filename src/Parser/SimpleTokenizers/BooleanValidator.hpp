//
// Created by caedus on 09.02.2021.
//

#include <optional>

#include "Parser/Interface/IValidator.hpp"

#include <memory>

namespace nastya::parser {

const std::string TRUE_VALUE = "#true";
const std::string FALSE_VALUE = "#false";

class BooleanValidator : public IValidator {
public:
    BooleanValidator(std::string true_string, std::string false_string);
    std::optional<Token> validate(const std::string& value, ParsingContext& context) const override;
    static std::unique_ptr<IValidator> create();
private:
    std::string m_true_value;
    std::string m_false_value;
};

}
