//
// Created by rfish on 7/10/2024.
//

#ifndef KOISCRIPT_LEXICON_HPP
#define KOISCRIPT_LEXICON_HPP


#include "scripting/token.hpp"

#include <unordered_map>
#include <string>


namespace Koi {
namespace Scripting {

class Lexicon {
protected:
    std::unordered_map<std::string, Token::Type> _keywords;

public:
    Lexicon();
    Token::Type get_type(const std::string& key) const;
    Token::Type get_type(const char* key) const;
};

} // Scripting
} // Koi

#endif //KOISCRIPT_LEXICON_HPP
