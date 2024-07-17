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

//todo:: add built-in functions as reserved ids
class Lexicon {
protected:
    std::unordered_map<char, Token::Type> _single_char_tokens;
    std::unordered_map<std::string, Token::Type> _keywords;

public:
    Lexicon();
    Token::Type get_type(const char& key, bool is_verbatim = false) const;
    Token::Type get_type(const std::string& key, bool is_verbatim = false) const;

    bool is_valid_id(const char& value) const;
    bool is_valid_int(const char& value) const;
    bool is_valid_id(const std::string& value) const;
    bool is_valid_int(const std::string& value) const;
    bool is_valid_float(const std::string& value) const;
};

} // Scripting
} // Koi

#endif //KOISCRIPT_LEXICON_HPP
