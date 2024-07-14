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

    char token_buffer[64];
    unsigned int i = 0u;
    while (it < end && i < 64u) {
        while (it != end && !std::isspace(*it)) {
            Token end_result = _evaluate(it, 1u);

            switch (end_result.type) {
                case Token::SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND:
                    result = _skip_comment(&it, end);
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_GROUPING_START:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_SCOPE_START:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_VALUE_START:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_ARRAY_START:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_GROUPING_END:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_SCOPE_END:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_VALUE_END:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_ARRAY_END:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_COMBINER:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_ASSIGNER:
                    break;
                case Token::SCRIPTING_TOKEN_TYPE_DELIMITER:
                    break;
            }

            if (end_result.type == Token::Type::SCRIPTING_TOKEN_TYPE_DELIMITER) {
                token_buffer[i] = *it;
                ++i;

                Token buffer_result = _evaluate(token_buffer, i);
                if (buffer_result.type != Token::Type::SCRIPTING_TOKEN_TYPE_INVALID) {
                    _tokens.emplace_back(buffer_result);
                    i = 0u;
                }

            } else if (end_result.type == Token::Type::SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND) {
                if (i > 0u) {
                    _tokens.emplace_back(_evaluate(token_buffer, i));
                    i = 0u;
                }

                ++it;

                bool is_bookend_found = false;
                const char* verbatim_it = it;
                while (verbatim_it != end && !is_bookend_found) {
                    is_bookend_found = _grammar.get_type(verbatim_it) == Token::Type::SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND;
                    ++verbatim_it;
                }

                it = verbatim_it;
            } else if (end_result.type == Token::Type::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND) {
                if (i > 0u) {
                    _tokens.emplace_back(_evaluate(token_buffer, i));
                    i = 0u;
                }

                _tokens.emplace_back(end_result);
                ++it;

                //todo:: iterate through the literal text value until bookend reached again
                bool is_bookend_found = false;
                const char* verbatim_it = it;
                while (verbatim_it != end && !is_bookend_found) {
                    is_bookend_found =
                            _grammar.get_type(verbatim_it) == Token::Type::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND;
                    ++verbatim_it;
                }

                unsigned long verbatim_size = verbatim_it - it - 1u;
                Token text(Token::Type::SCRIPTING_TOKEN_TYPE_VALUE, std::string(it, verbatim_size));
                _tokens.emplace_back(text);
                _tokens.emplace_back(_evaluate(verbatim_it, 1u));

                it = verbatim_it + 1u;

            } else {
                if (i > 0u) {
                    if (end_result.type == Token::SCRIPTING_TOKEN_TYPE_VALUE_START) {
                        _tokens.emplace_back(_evaluate(token_buffer, i));
                    } else if (end_result.type == Token::SCRIPTING_TOKEN_TYPE_VALUE_END) {
                        _tokens.emplace_back(Token::Type::SCRIPTING_TOKEN_TYPE_VALUE, std::string(token_buffer, i));
                    }

                    i = 0u;
                }

                _tokens.emplace_back(end_result);
            }

            ++it;
        }

        ++it;
    }

    return _tokens;
}


Lexer::Error Lexer::_skip_comment(const char** in_it, const char* end) const {
    Error result = SCRIPTING_LEXER_ERROR_OK;
    const char* it = *in_it;
    Token lex_result = _evaluate(it++, 1u);

    while (it != end && lex_result.type != Token::Type::SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND) {
        lex_result = _evaluate(it++, 1u);
    }

    if (it == end) {
        result = SCRIPTING_LEXER_ERROR_UNEXPECTED_EOF;
    } else {
        *in_it = it;
    }

    return result;
}


Token Lexer::_evaluate(const char* token_string, unsigned long size) const {
    Token result;

    result.value = std::string(token_string, size);
    result.type = _grammar.get_type(result.value);

    return result;
}

} // Scripting
} // Koi