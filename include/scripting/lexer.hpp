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
        SCRIPTING_LEXER_ERROR_SIZE
    };

protected:
    Lexicon _grammar;

public:
    Error lex(const char* script, unsigned long size, std::vector<Token>& out_tokens) const;

protected:
    Token _evaluate(const char* token_string, unsigned long size) const;
    Token _evaluate(const char* token_string, const char* end) const;
    Error _skip_comment(const char** in_it, const char* end, std::vector<Token>& out_tokens) const;
    Error _fill_text(const char** in_it, const char* end, std::vector<Token>& out_tokens) const;
    Error _fill_group(const char** in_it, const char* end, std::vector<Token>& out_tokens) const;
    Error _fill_id(const char** in_it, const char* end, std::vector<Token>& out_tokens) const;

};

} // Scripting
} // Koi

#endif //KOI_SCRIPTING_LEXER_HPP
