//
// Created by rfish on 7/10/2024.
//


#include "../include/scripting/lexer.hpp"

#include "../include/scripting/log/log.hpp"

#include <cstring>
#include <iostream>
#include <string>


namespace Koi { namespace Scripting {

const unsigned int Lexer::MAX_TOKEN_SIZE = 64u;


Lexer::Error Lexer::lex(const char* script, unsigned long size, std::vector<Token>& out_tokens) {
    Error result = SCRIPTING_LEXER_ERROR_OK;
    const char* it = script;
    const char* end = script + size;

    _is_lexing_verbatim = false;

    while (it != end && result == SCRIPTING_LEXER_ERROR_OK) {
        if (!_is_lexing_verbatim) {
            result = _lex(&it, end, out_tokens);
        } else {
            result = _lex_verbatim(&it, end, out_tokens);
        }
    }

    return result;
}


Lexer::Error Lexer::_lex(const char** start, const char* end, std::vector<Token>& out_tokens) {
    Error result = SCRIPTING_LEXER_ERROR_OK;
    const char* it = *start;

    char multi_char_token_backlog[MAX_TOKEN_SIZE];
    std::memset(multi_char_token_backlog, 0, MAX_TOKEN_SIZE);
    unsigned int i = 0u;

    Token::Type type = Token::SCRIPTING_TOKEN_TYPE_INVALID;

    while (it != end && !_is_lexing_verbatim && result == SCRIPTING_LEXER_ERROR_OK) {
        if (!out_tokens.empty() && out_tokens.back().value == ";") {
            int j = 0;
        }
        while (it != end && std::isspace(*it)) {
            ++it;
        }

        if (it != end) {
            type = _lexicon.get_type(*it, _is_lexing_verbatim);

            if (type != Token::SCRIPTING_TOKEN_TYPE_INVALID) {
                if (i > 0u) {
                    result = _add_multi_char_token(multi_char_token_backlog, i, out_tokens);
                    std::memset(multi_char_token_backlog, 0, i);
                    i = 0u;
                }

                if (result == SCRIPTING_LEXER_ERROR_OK) {
                    result = _add_single_char_token(*it, out_tokens);
                }

                if (type == Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND) {
                    _is_lexing_verbatim = true;
                }
            } else {
                if (i < MAX_TOKEN_SIZE) {
                    multi_char_token_backlog[i++] = *it;
                } else {
                    result = SCRIPTING_LEXER_TOKEN_TOO_LARGE;
                    KOI_LOG(std::string("Token too large. i=") + std::to_string(i) + std::string(", token=") + std::string(multi_char_token_backlog, i));
                }
            }

            ++it;
        }
    }

    if (result == SCRIPTING_LEXER_ERROR_OK) {
        *start = it;
    }

    return result;
}


Lexer::Error Lexer::_lex_verbatim(const char** start, const char* end, std::vector<Token>& out_tokens) {
    Error result = SCRIPTING_LEXER_ERROR_OK;
    const char* it = *start;

    char multi_char_token_backlog[MAX_TOKEN_SIZE];
    std::memset(multi_char_token_backlog, 0, MAX_TOKEN_SIZE);
    unsigned int i = 0u;

    while (it != end && _is_lexing_verbatim) {
        _is_lexing_verbatim = _lexicon.get_type(*it) != Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND;
        if (_is_lexing_verbatim) {
            if (i < MAX_TOKEN_SIZE) {
                multi_char_token_backlog[i++] = *it;
            } else {
                result = SCRIPTING_LEXER_TOKEN_TOO_LARGE;
                KOI_LOG(std::string("Token too large. i=") + std::to_string(i) + std::string(", token=") + std::string(multi_char_token_backlog, i));
            }
        }

        ++it;
    }

    if (it == end) {
        result = SCRIPTING_LEXER_ERROR_UNEXPECTED_EOF;
        KOI_LOG("Unexpected end of file.");
    }

    if (result == SCRIPTING_LEXER_ERROR_OK) {
        result = _add_multi_char_token(multi_char_token_backlog, i, out_tokens);
    } else {
        KOI_LOG("Failed to add multi char token.");
    }

    if (result == SCRIPTING_LEXER_ERROR_OK) {
        result = _add_single_char_token(*(it - 1u), out_tokens);
        KOI_LOG("Failed to add single char token.");
        *start = it;
    }

    return result;
}


Lexer::Error Lexer::_add_single_char_token(const char& value, std::vector<Token>& out_tokens) const {
    Error result = SCRIPTING_LEXER_ERROR_OK;

    Token::Type type = _lexicon.get_type(value, _is_lexing_verbatim);

    if (type != Token::SCRIPTING_TOKEN_TYPE_INVALID) {
        std::string value_string(1u, value);
        out_tokens.emplace_back(_lexicon.get_type(value), value_string);
    } else {
        result = SCRIPTING_LEXER_ERROR_INVALID_TOKEN;
        KOI_LOG(std::string("Invalid token. type=") + std::to_string(type) + std::string(" ") + std::string(1u, value));
    }

    return result;
}


Lexer::Error Lexer::_add_multi_char_token(const char* start, unsigned int size, std::vector<Token>& out_tokens) const {
    Error result = SCRIPTING_LEXER_ERROR_OK;

    std::string value_string(start, size);
    Token::Type type = _lexicon.get_type(value_string, _is_lexing_verbatim);

    if (type != Token::SCRIPTING_TOKEN_TYPE_INVALID) {
        out_tokens.emplace_back(_lexicon.get_type(value_string, _is_lexing_verbatim), value_string);
    } else {
        result = SCRIPTING_LEXER_ERROR_INVALID_TOKEN;
        KOI_LOG(std::string("Invalid token. type=") + std::to_string(type) + std::string(" ") + value_string);
    }

    return result;
}

} // Scripting
} // Koi