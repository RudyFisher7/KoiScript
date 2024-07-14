//
// Created by rfish on 7/10/2024.
//


#include "../include/scripting/lexer.hpp"

#include <iostream>
#include <string>


namespace Koi { namespace Scripting {

std::vector<Token>& Lexer::lex(const char* script, unsigned long size) {
    Error result = SCRIPTING_LEXER_ERROR_OK;
    const char* it = script;
    const char* end = script + size;

    unsigned int i = 0u;
    while (it < end && i < _token_buffer.size()) {
        while (it != end && !std::isspace(*it)) {
            Token end_result = _evaluate(it, 1u);

            switch (end_result.type) {
                case Token::SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND:
                    _tokens.push_back(end_result);
                    result = _skip_comment(&it, end);
                    _tokens.emplace_back(_evaluate(it, 1u));
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND:
                    _tokens.push_back(end_result);
                    result = _fill_text(&it, end, _token_buffer);
                    _tokens.emplace_back(_evaluate(_token_buffer.data(), _token_buffer.size()));
                    _tokens.emplace_back(_evaluate(it, 1u));
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_GROUPING_START:
                    _tokens.push_back(end_result);
                    _tokens.emplace_back(_evaluate(it, 1u));
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_SCOPE_START:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_VALUE_START:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_ARRAY_START:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_COMBINER:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_ASSIGNER:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_DELIMITER:
                    break;
            }

            ++it;
        }

        ++it;
    }

    return _tokens;
}


Token Lexer::_evaluate(const char* token_string, unsigned long size) const {
    Token result;

    result.value = std::string(token_string, size);
    result.type = _grammar.get_type(result.value);

    return result;
}


Lexer::Error Lexer::_skip_comment(const char** in_it, const char* end) const {
    Error result = SCRIPTING_LEXER_ERROR_OK;
    const char* it = *in_it;
    Token lex_result = _evaluate(++it, 1u);

    while (it != end && lex_result.type != Token::Type::SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND) {
        lex_result = _evaluate(++it, 1u);
    }

    if (it == end) {
        result = SCRIPTING_LEXER_ERROR_UNEXPECTED_EOF;
    } else {
        *in_it = ++it;
    }

    return result;
}


Lexer::Error Lexer::_fill_text(const char** in_it, const char* end, std::array<char, TOKEN_BUFFER_SIZE>& buffer) const {
    Error result = Lexer::SCRIPTING_LEXER_ERROR_OK;
    const char* it = *in_it;
    unsigned int i = 0u;
    Token lex_result = _evaluate(++it, 1u);

    while (it != end && lex_result.type != Token::Type::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND) {
        buffer.at(i++) = *it;
        lex_result = _evaluate(++it, 1u);
    }

    if (it == end) {
        result = SCRIPTING_LEXER_ERROR_UNEXPECTED_EOF;
    } else {
        lex_result = _evaluate(buffer.data(), buffer.size());
        *in_it = it;
    }

    return result;
}


Lexer::Error Lexer::_fill_group(const char** in_it, const char* end, std::array<char, TOKEN_BUFFER_SIZE>& buffer) const {
    Error result = Lexer::SCRIPTING_LEXER_ERROR_OK;
    const char* it = *in_it;
    unsigned int i = 0u;
    Token lex_result = _evaluate(++it, 1u);

    while (it != end && lex_result.type != Token::Type::SCRIPTING_TOKEN_TYPE_GROUPING_END) {
        while (it != end && lex_result.type != Token::Type::SCRIPTING_TOKEN_TYPE_TYPE) {
            buffer.at(i++) = *it;
            lex_result = _evaluate(++it, 1u);
        }
    }

    if (it == end) {
        result = SCRIPTING_LEXER_ERROR_UNEXPECTED_EOF;
    } else {
        lex_result = _evaluate(buffer.data(), buffer.size());
        *in_it = it;
    }

    return result;
}

} // Scripting
} // Koi