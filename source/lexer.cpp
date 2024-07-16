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

    while (it != end && result == SCRIPTING_LEXER_ERROR_OK) {
        Token end_token = _evaluate(it, 1u);

        switch (end_token.type) {
            case Token::SCRIPTING_TOKEN_TYPE_ID_START: {
                result = _fill_meta(token_start, it, out_tokens);
                if (result == SCRIPTING_LEXER_ERROR_OK) {
                    ++it;
                    result = _fill_id(&it, end, out_tokens);
                    token_start = it;
                }
            }
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
                result = _fill_group(&it, end, out_tokens);
                break;
            case Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START:
                break;
            case Token::SCRIPTING_TOKEN_TYPE_COMBINER:
                out_tokens.emplace_back(end_token);
                break;
            case Token::SCRIPTING_TOKEN_TYPE_DELIMITER:
                out_tokens.emplace_back(_evaluate(it, 1u));
                break;
            case Token::SCRIPTING_TOKEN_TYPE_ASSIGNER:
                out_tokens.emplace_back(_evaluate(token_start, it));
                out_tokens.emplace_back(_evaluate(it, 1u));
                token_start = it + 1u;
                break;
            case Token::SCRIPTING_TOKEN_TYPE_SCOPE_START:
                break;
            default: {
                Token multichar_token = _evaluate(token_start, it + 1);
                switch (multichar_token.type) {
                    case Token::SCRIPTING_TOKEN_TYPE_TYPE:
                        out_tokens.emplace_back(multichar_token);
                        break;
                }
            }
                break;
        }

        ++it;
    }

    return result;
}


Token Lexer::_evaluate(const char* token_string, unsigned int size) const {
    Token result;

    result.value = _get_clean_token_value(token_string, size);
    result.type = _lexicon.get_type(result.value);

    return result;
}

Token Lexer::_evaluate(const char* token_string, const char* end) const {
    Token result;

    result.value = _get_clean_token_value(token_string, end);
    result.type = _lexicon.get_type(result.value);

    return result;
}


std::string Lexer::_get_clean_token_value(const char* token_string, unsigned int size) const {
    unsigned int i = 0u;
    unsigned int j = 0u;
    while (i < MAX_TOKEN_SIZE && j < size) {
        while(j < size && std::isspace(token_string[j])) {
            ++j;
        }

        if (j < size) {
            _token_buffer[i] = token_string[j];
            ++j;
            ++i;
        }
    }

    return std::string(_token_buffer, i);
}


std::string Lexer::_get_clean_token_value(const char* token_string, const char* end) const {
    unsigned int i = 0u;
    while (i < MAX_TOKEN_SIZE && token_string != end) {
        while(token_string != end && std::isspace(*token_string)) {
            ++token_string;
        }

        if (token_string != end) {
            _token_buffer[i] = *token_string;
            ++token_string;
            ++i;
        }
    }

    return std::string(_token_buffer, i);
}


Lexer::Error Lexer::_skip_comment(const char** in_it, const char* end, std::vector<Token>& out_tokens) const {
    Error result = SCRIPTING_LEXER_ERROR_OK;
    const char* it = *in_it;
    Token lex_result = _evaluate(++it, 1u);

    while (it != end && lex_result.type != Token::SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND) {
        lex_result = _evaluate(++it, 1u);
    }

    if (it == end) {
        result = SCRIPTING_LEXER_ERROR_UNEXPECTED_EOF;
    } else {
        *in_it = ++it;
    }

    return result;
}


Lexer::Error Lexer::_fill_meta(const char* meta_start, const char* meta_end, std::vector<Token>& out_tokens) const {
    Error result = SCRIPTING_LEXER_ERROR_OK;

    Token meta = _evaluate(meta_start, meta_end);
    if (
            meta.type == Token::SCRIPTING_TOKEN_TYPE_LEFT_META
            || meta.type == Token::SCRIPTING_TOKEN_TYPE_RIGHT_META
    ) {
        out_tokens.emplace_back(meta);
    } else {
        result = SCRIPTING_LEXER_ERROR_UNRECOGNIZED_TOKEN;
    }

    return result;
}


Lexer::Error Lexer::_fill_id(const char** in_it, const char* end, std::vector<Token>& out_tokens) const {
    Error result = SCRIPTING_LEXER_ERROR_OK;
    const char* it = *in_it;
    Token lex_result;

    if (_lexicon.is_valid_id_char(*it)) {
        lex_result = _evaluate(it, 1u);
    } else {
        result = SCRIPTING_LEXER_ERROR_INVALID_ID;
    }

    while (it != end && _lexicon.get_type(_get_clean_token_value(it, 1u)) != Token::SCRIPTING_TOKEN_TYPE_ID_END) {
        ++it;

        while (std::isspace(*it)) {
            // skip whitespace
            ++it;
        }

        if (_lexicon.is_valid_id_char(*it)) {
        } else if (_lexicon.get_type(_get_clean_token_value(it, 1u)) != Token::SCRIPTING_TOKEN_TYPE_ID_END) {
            result = SCRIPTING_LEXER_ERROR_INVALID_ID;
        }
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
        out_tokens.emplace_back(Token::SCRIPTING_TOKEN_TYPE_ID, std::string(*in_it, it));
        *in_it = ++it;
    }

    return result;
}


Lexer::Error Lexer::_fill_text(const char** in_it, const char* end, std::vector<Token>& out_tokens) const {
    Error result = SCRIPTING_LEXER_ERROR_OK;
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
    Error result = SCRIPTING_LEXER_ERROR_OK;
    const char* it = *in_it;

    Token single_char_token = _evaluate(it++, 1u);

    // note: the first token has already been confirmed to be SCRIPTING_TOKEN_TYPE_GROUPING_START
    // before entering this function.
    out_tokens.emplace_back(single_char_token);

    bool can_iterate = it != end;

    const char* type_token_start = it;
    while (can_iterate) {
        single_char_token = _evaluate(++it, 1u);

        // there is parameter type in this group
        if (single_char_token.type == Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END) {
            out_tokens.emplace_back(single_char_token);
            type_token_start = it + 1u;
        } else if (
                single_char_token.type == Token::SCRIPTING_TOKEN_TYPE_SEPARATOR
                || single_char_token.type == Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START
        ) {
            if (it - type_token_start > 1u) {
                Token type_token = _evaluate(type_token_start, it);
                type_token_start = it;

                if (type_token.type == Token::SCRIPTING_TOKEN_TYPE_TYPE) {
                    out_tokens.emplace_back(type_token);
                    out_tokens.emplace_back(single_char_token);
                }
            }
        } else if (single_char_token.type == Token::SCRIPTING_TOKEN_TYPE_GROUPING_END) {
            out_tokens.emplace_back(single_char_token);
            can_iterate = false; // end of the group
        }

        if (it == end) {
            result = SCRIPTING_LEXER_ERROR_UNEXPECTED_EOF;
        }

        can_iterate = (
                can_iterate
                && single_char_token.type != Token::SCRIPTING_TOKEN_TYPE_GROUPING_END
                && result == SCRIPTING_LEXER_ERROR_OK
        );
    }

    if (result == SCRIPTING_LEXER_ERROR_OK) {
        *in_it = it;
    }

    return result;
}


Lexer::Error Lexer::_fill_array_size(const char** in_it, const char* end, std::vector<Token>& out_tokens) const {
    Error result = SCRIPTING_LEXER_ERROR_OK;
    const char* it = *in_it;

    Token single_char_token = _evaluate(it++, 1u);

    // note: the first token has already been confirmed to be SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START
    // before entering this function.
    out_tokens.emplace_back(single_char_token);

    const char* num_start = it;
    while (it != end && std::isdigit(*it)) {
        ++it;

        while (std::isspace(*it)) {
            // skip whitespace
            ++it;
        }
    }

    if (it != end) {
        single_char_token = _evaluate(it, 1u);
        if (single_char_token.type == Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END) {
            Token num_token(Token::SCRIPTING_TOKEN_TYPE_VALUE, _get_clean_token_value(num_start, it));
            out_tokens.emplace_back(single_char_token);
        }
    } else {
        result = SCRIPTING_LEXER_ERROR_UNEXPECTED_EOF;
    }


    if (result == Error::SCRIPTING_LEXER_ERROR_OK) {
        Token validation_result = _evaluate(*in_it, it);
        if (validation_result.type == Token::SCRIPTING_TOKEN_TYPE_RESERVED_ID) {
            result = Error::SCRIPTING_LEXER_ERROR_RESERVED_ID;
        }
    }

    if (result == Error::SCRIPTING_LEXER_ERROR_OK) {
        out_tokens.emplace_back(Token::SCRIPTING_TOKEN_TYPE_ID, std::string(*in_it, it));
        *in_it = ++it;
    }

    return result;
}

} // Scripting
} // Koi