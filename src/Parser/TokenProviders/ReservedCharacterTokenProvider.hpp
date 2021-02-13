//
// Created by caedus on 12.02.2021.
//

//
// Created by caedus on 11.02.2021.
//

#include <memory>
#include <optional>

#include "Parser/Interface/ITokenProvider.hpp"

namespace nastya::parser {

class ReservedCharacterTokenProvider : public ITokenProvider
{
public:
    ReservedCharacterTokenProvider() = default;
    std::optional<Token> getTokenIfAvailable(const std::string& value, ParsingContext& context) const override;
    static std::unique_ptr<ITokenProvider> create();
private:
    std::string m_label_regex;
};

}
