//
// Created by caedus on 11.02.2021.
//

#include "Tokenizer/TokenProviders/AtomicValueTokenProvider.hpp"
#include "Tokenizer/TokenProviders/BooleanTokenProvider.hpp"
#include "Tokenizer/TokenProviders/LabelTokenProvider.hpp"
#include "Tokenizer/TokenProviders/NumberTokenProvider.hpp"

namespace nastya::tokens {

AtomicValueTokenProvider::AtomicValueTokenProvider()
{
    addProvider(BooleanTokenProvider::create())
        .addProvider(NumberTokenProvider::create())
        .addProvider(LabelTokenProvider::create());
}

std::optional<Token>
AtomicValueTokenProvider::getTokenIfAvailable(const std::string& value, ParsingContext& context) const
{
    context.end_position = context.start_position;
    if (not isprint(value[context.end_position]))
    {
        return {};
    }
    std::stringstream ss;
    while (context.end_position < value.size() and not isblank(value[context.end_position])
           and value[context.end_position] != ')')
    {
        ss << value[context.end_position++];
    }
    const auto token = ss.str();
    return TokenProvidersAggregator::getTokenIfAvailable(token, context);
}

std::unique_ptr<ITokenProvider> AtomicValueTokenProvider::create()
{
    auto result = std::make_unique<AtomicValueTokenProvider>();
    return std::unique_ptr<ITokenProvider>(result.release());
}
}  // namespace nastya::tokens
