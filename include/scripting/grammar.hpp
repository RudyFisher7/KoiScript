//
// Created by rfish on 7/10/2024.
//

#ifndef KOISCRIPT_GRAMMAR_HPP
#define KOISCRIPT_GRAMMAR_HPP


#include "scripting/token.hpp"

#include <unordered_map>
#include <string>


namespace Koi {
namespace Scripting {

class Grammar {
protected:
    std::unordered_map<std::string, Token::Type> _keywords;

public:
    Grammar();
    Token::Type get_type(const std::string& key) const;
    Token::Type get_type(const char* key) const;
};

} // Scripting
} // Koi

#endif //KOISCRIPT_GRAMMAR_HPP
