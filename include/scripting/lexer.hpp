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
protected:
    Lexicon _grammar;
    std::vector<Token> _tokens;
public:
    std::vector<Token>& lex(const char* script, unsigned long size);

protected:
    Token evaluate(const char* token_string, unsigned long size) const;

};

} // Scripting
} // Koi

#endif //KOI_SCRIPTING_LEXER_HPP
