//
// Created by caedus on 11.02.2021.
//

#include <memory>
#include <optional>

#include "Tokenizer/Interface/ITokenProvider.hpp"

namespace nastya::tokens {

const std::string LABEL_REGEX = "[A-Za-z][A-Za-z0-9_-]*[A_Za-z0-9_]?";

class LabelTokenProvider : public ITokenProvider
{
public:
    LabelTokenProvider(std::string label_regex);
    std::optional<Token> getTokenIfAvailable(const std::string& value, ParsingContext& context) const override;
    static std::unique_ptr<ITokenProvider> create();
private:
    std::string m_label_regex;
};

}
