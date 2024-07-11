//
// Created by rfish on 7/10/2024.
//

#include "scripting/grammar.hpp"


namespace Koi {
namespace Scripting {

Grammar::Grammar() {
    _key_words = {
            {"int", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"float", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"text", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"void", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"id", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"ref", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"func", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"lib", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"(", Token::Type::SCRIPTING_TOKEN_TYPE_GROUPING_START},
            {")", Token::Type::SCRIPTING_TOKEN_TYPE_GROUPING_END},
            {"{", Token::Type::SCRIPTING_TOKEN_TYPE_SCOPE_START},
            {"}", Token::Type::SCRIPTING_TOKEN_TYPE_SCOPE_END},
            {"<", Token::Type::SCRIPTING_TOKEN_TYPE_VALUE_START},
            {">", Token::Type::SCRIPTING_TOKEN_TYPE_VALUE_END},
            {"'", Token::Type::SCRIPTING_TOKEN_TYPE_TEXT_BOOKEND},
            {".", Token::Type::SCRIPTING_TOKEN_TYPE_ACCESSOR},
            {"=", Token::Type::SCRIPTING_TOKEN_TYPE_ASSIGNER},
            {":", Token::Type::SCRIPTING_TOKEN_TYPE_FUNCTION_BODY_START},
            {";", Token::Type::SCRIPTING_TOKEN_TYPE_DELIMITER},
            {"return", Token::Type::SCRIPTING_TOKEN_TYPE_RESULTER},
    };
}


Token::Type Grammar::get_type(const std::string& key) const {
    Token::Type result = Token::Type::SCRIPTING_TOKEN_TYPE_INVALID;

    auto it = _key_words.find(key);

    if (it != _key_words.end()) {
        result = it->second;
    }

    return result;
}

} // Scripting
} // Koi