//
// Created by rfish on 7/10/2024.
//


#include "../include/scripting/lexer.hpp"

#include <iostream>
#include <string>


namespace Koi { namespace Scripting {

std::vector<Token>& Lexer::lex(const char* script, unsigned long size) {
    const char* it = script;
    const char* end = script + size;

    char token_buffer[64];
    unsigned int i = 0u;
    while (it < end && i < 64u) {
        while (it != end && !std::isspace(*it)) {
            Token end_result = evaluate(it, 1u);

            if (end_result.type == Token::Type::SCRIPTING_TOKEN_TYPE_INVALID) {
                token_buffer[i] = *it;
                ++i;

                Token buffer_result = evaluate(token_buffer, i);
                if (buffer_result.type != Token::Type::SCRIPTING_TOKEN_TYPE_INVALID) {
                    _tokens.emplace_back(buffer_result);
                    i = 0u;
                }

            } else if (end_result.type == Token::Type::SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND) {
                if (i > 0u) {
                    _tokens.emplace_back(evaluate(token_buffer, i));
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
                    _tokens.emplace_back(evaluate(token_buffer, i));
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
                _tokens.emplace_back(evaluate(verbatim_it, 1u));

                it = verbatim_it + 1u;

            } else {
                if (i > 0u) {
                    if (end_result.type == Token::SCRIPTING_TOKEN_TYPE_VALUE_START) {
                        _tokens.emplace_back(evaluate(token_buffer, i));
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


Token Lexer::evaluate(const char* token_string, unsigned long size) const {
    Token result;

    result.value = std::string(token_string, size);
    result.type = _grammar.get_type(result.value);

    return result;
}

} // Scripting
} // Koi