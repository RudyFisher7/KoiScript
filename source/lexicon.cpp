/*
 * MIT License
 *
 * Copyright (c) 2024 kiyasui-hito
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include "scripting/lexicon.hpp"


namespace Koi {
namespace Scripting {

Lexicon::Lexicon() {
    _tokens = {
            // mirrored enclosures
            {"(", Token::SCRIPTING_TOKEN_TYPE_GROUPING_START},
            {")", Token::SCRIPTING_TOKEN_TYPE_GROUPING_END},
            {"{", Token::SCRIPTING_TOKEN_TYPE_SCOPE_START},
            {"}", Token::SCRIPTING_TOKEN_TYPE_SCOPE_END},
            {"<", Token::SCRIPTING_TOKEN_TYPE_TEMPLATE_START},
            {">", Token::SCRIPTING_TOKEN_TYPE_TEMPLATE_END},

            // bookend enclosures
            {"\"", Token::SCRIPTING_TOKEN_TYPE_LITERAL_STRING_BOOKEND},
            {"#", Token::SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND},

            // operators
            {"&", Token::SCRIPTING_TOKEN_TYPE_OPERATOR_REFERENCE},
            {".", Token::SCRIPTING_TOKEN_TYPE_OPERATOR_MEMBER_ACCESS},
            {"->", Token::SCRIPTING_TOKEN_TYPE_OPERATOR_RETURN},
            {":", Token::SCRIPTING_TOKEN_TYPE_OPERATOR_INHERITANCE},
            {"::", Token::SCRIPTING_TOKEN_TYPE_OPERATOR_SCOPE},

            // delimiters
            {",", Token::SCRIPTING_TOKEN_TYPE_SEPARATOR},
            {";", Token::SCRIPTING_TOKEN_TYPE_DELIMITER},

            // built-in types
            {"object_t", Token::SCRIPTING_TOKEN_TYPE_BUILT_IN_TYPE_OBJECT},
            {"bool_t", Token::SCRIPTING_TOKEN_TYPE_BUILT_IN_TYPE_BOOL},
            {"char_t", Token::SCRIPTING_TOKEN_TYPE_BUILT_IN_TYPE_CHAR},
            {"int_t", Token::SCRIPTING_TOKEN_TYPE_BUILT_IN_TYPE_INT},
            {"float_t", Token::SCRIPTING_TOKEN_TYPE_BUILT_IN_TYPE_FLOAT},
            {"string_t", Token::SCRIPTING_TOKEN_TYPE_BUILT_IN_TYPE_STRING},

            // keywords
            {"false", Token::SCRIPTING_TOKEN_TYPE_LITERAL_BOOL_FALSE},
            {"true", Token::SCRIPTING_TOKEN_TYPE_LITERAL_BOOL_TRUE},
            {"class", Token::SCRIPTING_TOKEN_TYPE_CLASS},
            {"library", Token::SCRIPTING_TOKEN_TYPE_LIBRARY},
            {"import", Token::SCRIPTING_TOKEN_TYPE_IMPORT},
    };
}


Token::Type Lexicon::get_type(const std::string& key, bool is_verbatim) const {
    Token::Type result = Token::SCRIPTING_TOKEN_TYPE_INVALID;

    auto it = _tokens.find(key);

    if (it != _tokens.end()) {
        result = it->second;
    } else if (is_verbatim) {
        result = Token::SCRIPTING_TOKEN_TYPE_LITERAL_STRING;
    } else {
        result = get_non_bool_value_type(key);
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
    bool has_a_num = false;

    if (is_negative) {
        ++it;
    }

    bool has_decimal = false;
    while (result && it != end) {
        result = std::isdigit(*it);

        if (!has_a_num && result) {
            has_a_num = true;
        } else {
            if (!has_decimal) {
                has_decimal = *it == '.';
                if (has_decimal) {
                    result = true;
                }
            }
        }

        ++it;
    }

    return result && has_decimal && has_a_num;
}


Token::Type Lexicon::get_non_bool_value_type(const std::string& value) const {
    Token::Type result = Token::SCRIPTING_TOKEN_TYPE_INVALID;

    bool is_valid_num = true;

    auto it = value.cbegin();
    auto end = value.cend();

    bool is_negative = *it == '-';

    if (is_negative) {
        ++it;
    }

    bool has_a_num = false;
    bool has_decimal = false;
    while (is_valid_num && it != end) {
        is_valid_num = std::isdigit(*it);

        if (!has_a_num && is_valid_num) {
            has_a_num = true;
        } else {
            if (!has_decimal) {
                has_decimal = *it == '.';
                if (has_decimal) {
                    is_valid_num = true;
                }
            }
        }

        ++it;
    }

    if (has_a_num) {
        if (has_decimal) {
            result = Token::SCRIPTING_TOKEN_TYPE_LITERAL_FLOAT;
        } else if (is_valid_num) {
            result = Token::SCRIPTING_TOKEN_TYPE_LITERAL_INT;
        }
    }

    return result;
}

} // Scripting
} // Koi