//
// Created by caedus on 11.02.2021.
//

#include <optional>
#include <memory>

#include "Parser/Interface/IValidator.hpp"

namespace nastya::parser {

const std::string LABEL_REGEX = "[A-Za-z][A-Za-z0-9_-]*[A_Za-z0-9_]?";

class LabelValidator : public IValidator {
public:
    LabelValidator(std::string label_regex);
    std::optional<Token> validate(const std::string& value, ParsingContext& context) const override;
    static std::unique_ptr<IValidator> create();
private:
    std::string m_label_regex;
};

}
