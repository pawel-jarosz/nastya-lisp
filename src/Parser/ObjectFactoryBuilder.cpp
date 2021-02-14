#include "Parser/ObjectFactoryBuilder.hpp"
#include "TypeSystem/Types/BooleanObject.hpp"
#include "TypeSystem/Types/LabelObject.hpp"
#include "TypeSystem/Types/NumberObject.hpp"
#include "TypeSystem/Types/StringObject.hpp"

namespace nastya::lisp {

template <typename ObjectClass, typename Creator>
ObjectClass* callback(const tokens::Token& t)
{
    return new ObjectClass(std::get<Creator>(t.value));
}

ObjectFactoryBuilder::ObjectFactoryBuilder(IObjectFactory& factory) : m_factory{factory}
{
}

void ObjectFactoryBuilder::build()
{
    m_factory.registerToken(tokens::TokenType::Boolean, [](const tokens::Token& token) {
        return callback<typesystem::BooleanObject, bool>(token);
    });
    m_factory.registerToken(tokens::TokenType::Label, [](const tokens::Token& token) {
        return callback<typesystem::LabelObject, std::string>(token);
    });
    m_factory.registerToken(tokens::TokenType::String, [](const tokens::Token& token) {
        return callback<typesystem::StringObject, std::string>(token);
    });
    m_factory.registerToken(tokens::TokenType::Integer,
                            [](const tokens::Token& token) { return callback<typesystem::NumberObject, int>(token); });
    m_factory.registerToken(tokens::TokenType::Floating, [](const tokens::Token& token) {
        return callback<typesystem::NumberObject, float>(token);
    });
}

}  // namespace nastya::lisp
