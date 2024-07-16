//
// Created by rfish on 7/10/2024.
//

#include "scripting/lexicon.hpp"


namespace Koi {
namespace Scripting {

Lexicon::Lexicon() {
    _keywords = {
            // var types
            {"void", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"bool", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"int", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"float", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},
            {"text", Token::Type::SCRIPTING_TOKEN_TYPE_TYPE},

            // left metas
            {"var", Token::Type::SCRIPTING_TOKEN_TYPE_LEFT_META},
            {"fun", Token::Type::SCRIPTING_TOKEN_TYPE_LEFT_META},
            {"id", Token::Type::SCRIPTING_TOKEN_TYPE_LEFT_META},

            // right metas
            {"ref", Token::Type::SCRIPTING_TOKEN_TYPE_RIGHT_META},
            {"val", Token::Type::SCRIPTING_TOKEN_TYPE_RIGHT_META},
            {"exe", Token::Type::SCRIPTING_TOKEN_TYPE_RIGHT_META},

            // mirrored enclosures
            {"(", Token::Type::SCRIPTING_TOKEN_TYPE_GROUPING_START},
            {")", Token::Type::SCRIPTING_TOKEN_TYPE_GROUPING_END},
            {"{", Token::Type::SCRIPTING_TOKEN_TYPE_SCOPE_START},
            {"}", Token::Type::SCRIPTING_TOKEN_TYPE_SCOPE_END},
            {"<", Token::Type::SCRIPTING_TOKEN_TYPE_ID_START},
            {">", Token::Type::SCRIPTING_TOKEN_TYPE_ID_END},
            {"[", Token::Type::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START},
            {"]", Token::Type::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END},

            // bookend enclosures
            {"'", Token::Type::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND},
            {"#", Token::Type::SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND},

            // operators
            {"=", Token::Type::SCRIPTING_TOKEN_TYPE_ASSIGNER},

            // delimiters
            {":", Token::Type::SCRIPTING_TOKEN_TYPE_COMBINER},
            {",", Token::Type::SCRIPTING_TOKEN_TYPE_SEPARATOR},
            {";", Token::Type::SCRIPTING_TOKEN_TYPE_DELIMITER},

            // resulters
            {"ret", Token::Type::SCRIPTING_TOKEN_TYPE_RESULTER},
            {"_args", Token::Type::SCRIPTING_TOKEN_TYPE_RESERVED_ID},
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


bool Lexicon::is_valid_id_char(const char& value) const {
    return std::isalnum(value) || value == '_';
}

} // Scripting
} // Koi