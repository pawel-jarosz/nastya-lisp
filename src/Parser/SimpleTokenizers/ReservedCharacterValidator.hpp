//
// Created by caedus on 12.02.2021.
//

//
// Created by caedus on 11.02.2021.
//

#include <optional>
#include <memory>

#include "Parser/Interface/IValidator.hpp"

namespace nastya::parser {

class ReservedCharacterValidator : public IValidator {
public:
    ReservedCharacterValidator() = default;
    std::optional<Token> validate(const std::string& value, ParsingContext& context) const override;
    static std::unique_ptr<IValidator> create();
private:
    std::string m_label_regex;
};

}
