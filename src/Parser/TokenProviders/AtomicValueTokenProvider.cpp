//
// Created by caedus on 11.02.2021.
//

#include "Parser/TokenProviders/AtomicValueTokenProvider.hpp"
#include "Parser/TokenProviders/BooleanTokenProvider.hpp"
#include "Parser/TokenProviders/LabelTokenProvider.hpp"
#include "Parser/TokenProviders/NumberTokenProvider.hpp"

namespace nastya::parser {

std::optional<Token> AtomicValueTokenProvider::getTokenIfAvailable(const std::string& value, ParsingContext& context) const
{
    context.end_position = context.start_position;
    if (not isprint(value[context.end_position]))
    {
        return {};
    }
    std::stringstream ss;
    while (context.end_position < value.size() and not isblank(value[context.end_position]) and value[context.end_position] != ')')
    {
        ss << value[context.end_position++];
    }
    const auto token = ss.str();
    return TokenProvidersAggregator::getTokenIfAvailable(token, context);

}

std::unique_ptr<ITokenProvider> AtomicValueTokenProvider::create()
{
    auto result = std::make_unique<AtomicValueTokenProvider>();
    result->addValidator(BooleanTokenProvider::create())
        .addValidator(NumberTokenProvider::create())
        .addValidator(LabelTokenProvider::create());
    return std::unique_ptr<ITokenProvider>(result.release());
}
}

