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

    const char* token_start = it;

    while (it != end) {
        Token end_result = _evaluate(it, 1u);

        switch (end_result.type) {
            case Token::SCRIPTING_TOKEN_TYPE_ID_START:
                out_tokens.emplace_back(_evaluate(token_start, it));
                out_tokens.emplace_back(_evaluate(it, 1u));
                _fill_id(&it, end, out_tokens);
                token_start = it;
                break;
            case Token::SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND:
                result = _skip_comment(&it, end, out_tokens);
                token_start = it;
                break;
            case Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND:
                result = _fill_text(&it, end, out_tokens);
                token_start = it;
                break;
            case Token::SCRIPTING_TOKEN_TYPE_GROUPING_START:
                out_tokens.push_back(end_result);
                result = _fill_group(&it, end, out_tokens);
                out_tokens.emplace_back(_evaluate(it, 1u));
                break;
            case Token::SCRIPTING_TOKEN_TYPE_SCOPE_START:
                break;
            case Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START:
                break;
            case Token::SCRIPTING_TOKEN_TYPE_COMBINER:
                break;
            case Token::SCRIPTING_TOKEN_TYPE_ASSIGNER:
                out_tokens.emplace_back(_evaluate(token_start, it));
                out_tokens.emplace_back(_evaluate(it, 1u));
                token_start = it + 1u;
                break;
            case Token::SCRIPTING_TOKEN_TYPE_DELIMITER:
                out_tokens.emplace_back(_evaluate(it, 1u));
                break;
            default:
                break;
        }

        ++it;
    }

    return result;
}


Token Lexer::_evaluate(const char* token_string, unsigned long size) const {
    Token result;

    result.value = std::string(token_string, size);
    result.type = _grammar.get_type(result.value);

    return result;
}

Token Lexer::_evaluate(const char* token_string, const char* end) const {
    Token result;

    result.value = std::string(token_string, end);
    result.type = _grammar.get_type(result.value);

    return result;
}


Lexer::Error Lexer::_skip_comment(const char** in_it, const char* end, std::vector<Token>& out_tokens) const {
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


Lexer::Error Lexer::_fill_text(const char** in_it, const char* end, std::vector<Token>& out_tokens) const {
    Error result = Lexer::SCRIPTING_LEXER_ERROR_OK;
    const char* it = *in_it;
    Token lex_result = _evaluate(++it, 1u);

    while (it != end && lex_result.type != Token::Type::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND) {
        lex_result = _evaluate(++it, 1u);
    }

    if (it == end) {
        result = SCRIPTING_LEXER_ERROR_UNEXPECTED_EOF;
    } else {
        out_tokens.emplace_back(Token::SCRIPTING_TOKEN_TYPE_VALUE, std::string(*in_it, it));
        *in_it = it;
    }

    return result;
}


Lexer::Error Lexer::_fill_group(const char** in_it, const char* end, std::vector<Token>& out_tokens) const {
    Error result = Lexer::SCRIPTING_LEXER_ERROR_OK;
    const char* it = *in_it;
    Token lex_result = _evaluate(++it, 1u);

    while (it != end && lex_result.type != Token::Type::SCRIPTING_TOKEN_TYPE_GROUPING_END) {
        while (it != end && lex_result.type != Token::Type::SCRIPTING_TOKEN_TYPE_TYPE) {
            lex_result = _evaluate(++it, 1u);
        }
    }

    if (it == end) {
        result = SCRIPTING_LEXER_ERROR_UNEXPECTED_EOF;
    } else {
        *in_it = it;
    }

    return result;
}


Lexer::Error Lexer::_fill_id(const char** in_it, const char* end, std::vector<Token>& out_tokens) const {
    Error result = Lexer::SCRIPTING_LEXER_ERROR_OK;
    const char* it = *in_it;
    Token lex_result = _evaluate(++it, 1u);

    while (it != end && lex_result.type != Token::Type::SCRIPTING_TOKEN_TYPE_ID_END) {
        while (std::isspace(*it)) {
            // skip whitespace
        }

        lex_result = _evaluate(++it, 1u);
    }

    if (it == end) {
        result = SCRIPTING_LEXER_ERROR_UNEXPECTED_EOF;
    }

    if (result == Error::SCRIPTING_LEXER_ERROR_OK) {
        Token validation_result = _evaluate(*in_it, it);
        if (validation_result.type == Token::SCRIPTING_TOKEN_TYPE_RESERVED_ID) {
            result = Error::SCRIPTING_LEXER_ERROR_RESERVED_ID;
        }
    }

    if (result == Error::SCRIPTING_LEXER_ERROR_OK) {
        out_tokens.emplace_back(Token::SCRIPTING_TOKEN_TYPE_VALUE, std::string(*in_it, it));
        out_tokens.push_back(lex_result);
        *in_it = ++it;
    }

    return result;
}

} // Scripting
} // Koi