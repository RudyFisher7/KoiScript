//
// Created by rfish on 7/10/2024.
//


#ifndef KOI_SCRIPTING_LEXER_HPP
#define KOI_SCRIPTING_LEXER_HPP


#include "scripting/lexicon.hpp"
#include "scripting/token.hpp"

#include <array>
#include <vector>


namespace Koi { namespace Scripting {

class Lexer {
public:
    enum Error: int {
        SCRIPTING_LEXER_ERROR_UNKNOWN = -1,
        SCRIPTING_LEXER_ERROR_MIN = 0,
        SCRIPTING_LEXER_ERROR_OK = SCRIPTING_LEXER_ERROR_MIN,
        SCRIPTING_LEXER_ERROR_UNEXPECTED_EOF,
        SCRIPTING_LEXER_ERROR_RESERVED_ID,
        SCRIPTING_LEXER_ERROR_UNRECOGNIZED_TOKEN,
        SCRIPTING_LEXER_ERROR_INVALID_TOKEN,
        SCRIPTING_LEXER_ERROR_INVALID_ID,
        SCRIPTING_LEXER_TOKEN_TOO_LARGE
    };

protected:
    static const unsigned int MAX_TOKEN_SIZE = 64u;

    Lexicon _lexicon;
    mutable bool _is_verbatim = false;

    mutable char _token_buffer[MAX_TOKEN_SIZE];//todo:: cleanup

public:
    Error lex(const char* script, unsigned long size, std::vector<Token>& out_tokens) const;

protected:
    bool _is_single_char_token(const char* value) const;
    Error _add_single_char_token(const char* value, std::vector<Token>& out_tokens) const;
    bool _is_multi_char_token(const char* start, unsigned int size) const;
    Error _add_multi_char_token(const char* start, unsigned int size, std::vector<Token>& out_tokens) const;
};

} // Scripting
} // Koi

#endif //KOI_SCRIPTING_LEXER_HPP
