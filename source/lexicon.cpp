//
// Created by rfish on 7/10/2024.
//

#include "scripting/lexicon.hpp"


namespace Koi {
namespace Scripting {

Lexicon::Lexicon() {
    _single_char_tokens = {
            // mirrored enclosures
            {'(', Token::SCRIPTING_TOKEN_TYPE_GROUPING_START},
            {')', Token::SCRIPTING_TOKEN_TYPE_GROUPING_END},
            {'{', Token::SCRIPTING_TOKEN_TYPE_SCOPE_START},
            {'}', Token::SCRIPTING_TOKEN_TYPE_SCOPE_END},
            {'<', Token::SCRIPTING_TOKEN_TYPE_ID_START},
            {'>', Token::SCRIPTING_TOKEN_TYPE_ID_END},
            {'[', Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START},
            {']', Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END},

            // bookend enclosures
            {'\'', Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND},
            {'#', Token::SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND},

            // operators
            {'=', Token::SCRIPTING_TOKEN_TYPE_ASSIGNER},

            // delimiters
            {':', Token::SCRIPTING_TOKEN_TYPE_COMBINER},
            {',', Token::SCRIPTING_TOKEN_TYPE_SEPARATOR},
            {';', Token::SCRIPTING_TOKEN_TYPE_DELIMITER},
    };

    _keywords = {
            // var types
            {"void", Token::SCRIPTING_TOKEN_TYPE_TYPE},
            {"bool", Token::SCRIPTING_TOKEN_TYPE_TYPE},
            {"int", Token::SCRIPTING_TOKEN_TYPE_TYPE},
            {"float", Token::SCRIPTING_TOKEN_TYPE_TYPE},
            {"text", Token::SCRIPTING_TOKEN_TYPE_TYPE},

            // left metas
            {"var", Token::SCRIPTING_TOKEN_TYPE_LEFT_META},
            {"fun", Token::SCRIPTING_TOKEN_TYPE_LEFT_META},
            {"id", Token::SCRIPTING_TOKEN_TYPE_LEFT_META},

            // right metas
            {"ref", Token::SCRIPTING_TOKEN_TYPE_RIGHT_META},
            {"val", Token::SCRIPTING_TOKEN_TYPE_RIGHT_META},
            {"exe", Token::SCRIPTING_TOKEN_TYPE_RIGHT_META},

            // resulters
            {"ret", Token::SCRIPTING_TOKEN_TYPE_RESULTER},

            // reserved keywords
            {"true", Token::SCRIPTING_TOKEN_TYPE_BOOL},
            {"false", Token::SCRIPTING_TOKEN_TYPE_BOOL},

            // reserved ids
            {"_args", Token::SCRIPTING_TOKEN_TYPE_RESERVED_ID},
    };
}


Token::Type Lexicon::get_type(const char& key, bool is_verbatim) const {
    Token::Type result = Token::SCRIPTING_TOKEN_TYPE_INVALID;

    auto it = _single_char_tokens.find(key);

    if (it != _single_char_tokens.end()) {
        result = it->second;
    }

    return result;
}


Token::Type Lexicon::get_type(const std::string& key, bool is_verbatim) const {
    Token::Type result = Token::SCRIPTING_TOKEN_TYPE_INVALID;

    auto it = _keywords.find(key);

    if (it != _keywords.end()) {
        result = it->second;
    } else if (is_valid_int(key) || is_valid_float(key) || is_verbatim) {
        result = Token::SCRIPTING_TOKEN_TYPE_VALUE;
    } else if (is_valid_id(key)) {
        result = Token::SCRIPTING_TOKEN_TYPE_ID;
    }

    return result;
}


bool Lexicon::is_valid_id(const char& value) const {
    return std::isalnum(value) || value == '_';
}


bool Lexicon::is_valid_int(const char& value) const {
    return std::isdigit(value);
}


bool Lexicon::is_valid_id(const std::string& value) const {
    bool result = true;

    auto it = value.cbegin();
    auto end = value.cend();
    while (result && it != end) {
        result = is_valid_id(*it);
        ++it;
    }

    return result;
}


bool Lexicon::is_valid_int(const std::string& value) const {
    bool result = true;

    auto it = value.cbegin();
    auto end = value.cend();

    bool is_negative = *it == '-';

    if (is_negative) {
        ++it;
    }

    while (result && it != end) {
        result = std::isdigit(*it);
        ++it;
    }

    return result;
}


bool Lexicon::is_valid_float(const std::string& value) const {
    bool result = true;

    auto it = value.cbegin();
    auto end = value.cend();

    bool is_negative = *it == '-';

    if (is_negative) {
        ++it;
    }

    bool has_decimal = false;
    while (result && it != end) {
        result = std::isdigit(*it);

        if (!result && !has_decimal) {
            has_decimal = *it == '.';
            if (has_decimal) {
                result = true;
            }
        }

        ++it;
    }

    return result && has_decimal;
}

} // Scripting
} // Koi