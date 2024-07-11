//
// Created by rfish on 7/10/2024.
//

#ifndef KOI_SCRIPTING_LEXER_HPP
#define KOI_SCRIPTING_LEXER_HPP


#include "../include/scripting/grammar.hpp"
#include "../include/scripting/token.hpp"
#include "../include/scripting/variant.hpp"


namespace Koi { namespace Scripting {

class Lexer {
protected:
    Grammar _grammar;
public:
    void lex(const char* script, unsigned long size);


protected:
    Token evaluate(const char* token_string, unsigned long size) const;

};

} // Scripting
} // Koi

#endif //KOI_SCRIPTING_LEXER_HPP
