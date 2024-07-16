//
// Created by rfish on 7/10/2024.
//


#include "../include/scripting/lexer.hpp"

#include <iostream>
#include <string>


namespace Koi { namespace Scripting {

Lexer::Error Lexer::lex(const char* script, unsigned long size, std::vector<Token>& out_tokens) const {
    Error result = SCRIPTING_LEXER_ERROR_OK;
    const char* it = script;
    const char* end = script + size;

    char multi_char_token_backlog[MAX_TOKEN_SIZE];
    unsigned int i = 0u;

    while (it != end && result == SCRIPTING_LEXER_ERROR_OK) {
        if (!_is_verbatim) {
            while (std::isspace(*it)) {
                ++it;
            }
        } else {
            while (it != end && _lexicon.get_type(std::string(1u, *it)) != Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND) {
                multi_char_token_backlog[i++] = *it;
                ++it;
            }

            if (_lexicon.get_type(std::string(1u, *it)) != Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND) {
                result = _add_multi_char_token(multi_char_token_backlog, i, out_tokens);
                i = 0u;
                _is_verbatim = false;
            } else {
                result = SCRIPTING_LEXER_ERROR_UNEXPECTED_EOF;
            }
        }

        if (it != end) {
            bool was_single_char_token = _is_single_char_token(it);

            if (was_single_char_token) {
                if (i > 0u) {
                    if (_is_multi_char_token(multi_char_token_backlog, i)) {
                        result = _add_multi_char_token(multi_char_token_backlog, i, out_tokens);
                        i = 0u;
                    } else {
                        result = SCRIPTING_LEXER_ERROR_INVALID_TOKEN;
                    }
                }

                result = _add_single_char_token(it, out_tokens);

                if (out_tokens.back().type == Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND) {
                    _is_verbatim = !_is_verbatim;
                }
            } else {
                if (i < MAX_TOKEN_SIZE) {
                    multi_char_token_backlog[i++] = *it;
                } else {
                    result = SCRIPTING_LEXER_TOKEN_TOO_LARGE;
                }
            }
        }

        ++it;
    }

    return result;
}


bool Lexer::_is_single_char_token(const char* start) const {
    bool result = false;

    const char* end = start + 1u;
    switch (_lexicon.get_type(std::string(start, end))) {
        case Token::SCRIPTING_TOKEN_TYPE_GROUPING_START:
        case Token::SCRIPTING_TOKEN_TYPE_GROUPING_END:
        case Token::SCRIPTING_TOKEN_TYPE_SCOPE_START:
        case Token::SCRIPTING_TOKEN_TYPE_SCOPE_END:
        case Token::SCRIPTING_TOKEN_TYPE_ID_START:
        case Token::SCRIPTING_TOKEN_TYPE_ID_END:
        case Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START:
        case Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END:
        case Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND:
        case Token::SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND:
        case Token::SCRIPTING_TOKEN_TYPE_ASSIGNER:
        case Token::SCRIPTING_TOKEN_TYPE_COMBINER:
        case Token::SCRIPTING_TOKEN_TYPE_SEPARATOR:
        case Token::SCRIPTING_TOKEN_TYPE_DELIMITER:
        case Token::SCRIPTING_TOKEN_TYPE_RESULTER:
            result = true;
            break;
        case Token::SCRIPTING_TOKEN_TYPE_INVALID:
        case Token::SCRIPTING_TOKEN_TYPE_UNKNOWN:
        case Token::SCRIPTING_TOKEN_TYPE_VALUE:
        case Token::SCRIPTING_TOKEN_TYPE_ID:
        case Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE:
        case Token::SCRIPTING_TOKEN_TYPE_TYPE:
        case Token::SCRIPTING_TOKEN_TYPE_LEFT_META:
        case Token::SCRIPTING_TOKEN_TYPE_RIGHT_META:
        case Token::SCRIPTING_TOKEN_TYPE_RESERVED_ID:
        case Token::SCRIPTING_TOKEN_TYPE_SIZE:
        default:
            result = false;
            break;
    }

    return result;
}


Lexer::Error Lexer::_add_single_char_token(const char* start, std::vector<Token>& out_tokens) const {
    Error result = SCRIPTING_LEXER_ERROR_OK;

    const char* end = start + 1u;
    std::string value_string(start, end);
    out_tokens.emplace_back(_lexicon.get_type(value_string), value_string);

    return result;
}


bool Lexer::_is_multi_char_token(const char* start, unsigned int size) const {
    bool result = false;

    std::string value(start, size);
    switch (_lexicon.get_type(value, _is_verbatim)) {
        case Token::SCRIPTING_TOKEN_TYPE_INVALID:
        case Token::SCRIPTING_TOKEN_TYPE_UNKNOWN:
        case Token::SCRIPTING_TOKEN_TYPE_VALUE:
        case Token::SCRIPTING_TOKEN_TYPE_ID:
        case Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE:
        case Token::SCRIPTING_TOKEN_TYPE_TYPE:
        case Token::SCRIPTING_TOKEN_TYPE_LEFT_META:
        case Token::SCRIPTING_TOKEN_TYPE_RIGHT_META:
        case Token::SCRIPTING_TOKEN_TYPE_RESERVED_ID:
        case Token::SCRIPTING_TOKEN_TYPE_SIZE:
            result = true;
            break;
        case Token::SCRIPTING_TOKEN_TYPE_GROUPING_START:
        case Token::SCRIPTING_TOKEN_TYPE_GROUPING_END:
        case Token::SCRIPTING_TOKEN_TYPE_SCOPE_START:
        case Token::SCRIPTING_TOKEN_TYPE_SCOPE_END:
        case Token::SCRIPTING_TOKEN_TYPE_ID_START:
        case Token::SCRIPTING_TOKEN_TYPE_ID_END:
        case Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START:
        case Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END:
        case Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND:
        case Token::SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND:
        case Token::SCRIPTING_TOKEN_TYPE_ASSIGNER:
        case Token::SCRIPTING_TOKEN_TYPE_COMBINER:
        case Token::SCRIPTING_TOKEN_TYPE_SEPARATOR:
        case Token::SCRIPTING_TOKEN_TYPE_DELIMITER:
        case Token::SCRIPTING_TOKEN_TYPE_RESULTER:
        default:
            result = false;
            break;
    }

    return result;
}


Lexer::Error Lexer::_add_multi_char_token(const char* start, unsigned int size, std::vector<Token>& out_tokens) const {
    Error result = SCRIPTING_LEXER_ERROR_OK;

    std::string value_string(start, size);
    out_tokens.emplace_back(_lexicon.get_type(value_string, _is_verbatim), value_string);

    return result;
}

} // Scripting
} // Koi