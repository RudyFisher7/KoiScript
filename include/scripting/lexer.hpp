//
// Created by rfish on 7/10/2024.
//


#ifndef KOI_SCRIPTING_LEXER_HPP
#define KOI_SCRIPTING_LEXER_HPP


#include "../include/scripting/lexicon.hpp"
#include "../include/scripting/token.hpp"

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
        SCRIPTING_LEXER_ERROR_SIZE
    };

protected:
    struct TokenBuffer final {
    public:
        static const unsigned int TOKEN_BUFFER_SIZE = 64u;
        std::array<char, TOKEN_BUFFER_SIZE> buffer {};
        unsigned int current_index = 0u;
    };

    TokenBuffer _token_buffer;
    Lexicon _grammar;
    std::vector<Token> _tokens;
public:
    std::vector<Token>& lex(const char* script, unsigned long size);

protected:
    Token _evaluate(const char* token_string, unsigned long size) const;
    Error _skip_comment(const char** in_it, const char* end) const;
    Error _fill_text(const char** in_it, const char* end, TokenBuffer& buffer) const;
    Error _fill_group(const char** in_it, const char* end, TokenBuffer& buffer) const;

};

} // Scripting
} // Koi

#endif //KOI_SCRIPTING_LEXER_HPP
