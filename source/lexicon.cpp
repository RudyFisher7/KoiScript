//
// Created by rfish on 7/10/2024.
//

#include "scripting/lexicon.hpp"


namespace Koi {
namespace Scripting {

Lexicon::Lexicon() {
    _keywords = {
            // types
            {"void", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"bool", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"int", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"float", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"text", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"func", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},

            // metas
            {"dec", Token::Type::SCRIPTING_TOKEN_TYPE_META},
            {"id", Token::Type::SCRIPTING_TOKEN_TYPE_META},
            {"ref", Token::Type::SCRIPTING_TOKEN_TYPE_META},
            {"val", Token::Type::SCRIPTING_TOKEN_TYPE_META},

            // mirrored enclosures
            {"(", Token::Type::SCRIPTING_TOKEN_TYPE_GROUPING_START},
            {")", Token::Type::SCRIPTING_TOKEN_TYPE_GROUPING_END},
            {"{", Token::Type::SCRIPTING_TOKEN_TYPE_SCOPE_START},
            {"}", Token::Type::SCRIPTING_TOKEN_TYPE_SCOPE_END},
            {"<", Token::Type::SCRIPTING_TOKEN_TYPE_VALUE_START},
            {">", Token::Type::SCRIPTING_TOKEN_TYPE_VALUE_END},

            // bookend enclosures
            {"'", Token::Type::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND},
            {"#", Token::Type::SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND},

            // operators
            {"=", Token::Type::SCRIPTING_TOKEN_TYPE_ASSIGNER},
            {":", Token::Type::SCRIPTING_TOKEN_TYPE_COMBINER},
            {";", Token::Type::SCRIPTING_TOKEN_TYPE_DELIMITER},
            {",", Token::Type::SCRIPTING_TOKEN_TYPE_DELIMITER},

            // resulter
            {"return", Token::Type::SCRIPTING_TOKEN_TYPE_RESULTER},
    };
}


Token::Type Lexicon::get_type(const std::string& key) const {
    Token::Type result = Token::Type::SCRIPTING_TOKEN_TYPE_INVALID;

    auto it = _keywords.find(key);

    if (it != _keywords.end()) {
        result = it->second;
    }

    return result;
}

Token::Type Lexicon::get_type(const char* key) const {
    Token::Type result = Token::Type::SCRIPTING_TOKEN_TYPE_INVALID;

    auto it = _keywords.find(std::string(key, 1));

    if (it != _keywords.end()) {
        result = it->second;
    }

    return result;
}

} // Scripting
} // Koi