//
// Created by rfish on 7/10/2024.
//


#ifndef KOI_SCRIPTING_LEXER_HPP
#define KOI_SCRIPTING_LEXER_HPP


#include "../include/scripting/lexicon.hpp"
#include "../include/scripting/token.hpp"

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
    Lexicon _grammar;
    std::vector<Token> _tokens;
public:
    std::vector<Token>& lex(const char* script, unsigned long size);

protected:
    Error _skip_comment(const char** in_it, const char* end) const;
    Token _evaluate(const char* token_string, unsigned long size) const;

};

} // Scripting
} // Koi

#endif //KOI_SCRIPTING_LEXER_HPP
