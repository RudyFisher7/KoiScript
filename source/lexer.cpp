//
// Created by rfish on 7/10/2024.
//


#include "../include/scripting/lexer.hpp"

#include <iostream>
#include <vector>


namespace Koi { namespace Scripting {

void Lexer::lex(const char* script, unsigned long size) {
    const char* it = script;
    const char* end = script + size;

    std::vector<Token> tokens;
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
                    tokens.emplace_back(buffer_result);
                    i = 0u;
                }

            } else if (end_result.type == Token::Type::SCRIPTING_TOKEN_TYPE_TEXT_BOOKEND) {
                //todo:: emplace with buffer result if any
                tokens.emplace_back(end_result);

                //todo:: iterate through the literal text value until bookend reached again
//                while (it != end && )
            } else {
                if (i > 0u) {
                    if (end_result.type == Token::SCRIPTING_TOKEN_TYPE_VALUE_START) {
                        tokens.emplace_back(evaluate(token_buffer, i));
                    } else if (end_result.type == Token::SCRIPTING_TOKEN_TYPE_VALUE_END) {
                        tokens.emplace_back(Token::Type::SCRIPTING_TOKEN_TYPE_VALUE, Variant(token_buffer, i));
                    }

                    i = 0u;
                }

                tokens.emplace_back(end_result);
            }

            ++it;
        }

        ++it;
    }

    std::cout << std::endl;
}


Token Lexer::evaluate(const char* token_string, unsigned long size) const {
    Token result;

    result.value = Variant(token_string, size);
    result.type = _grammar.get_type(result.value.get_string());

    return result;
}

} // Scripting
} // Koi