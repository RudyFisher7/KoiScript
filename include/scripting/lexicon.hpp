/*
 * MIT License
 *
 * Copyright (c) 2024 kiyasui-hito
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


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
    Token::Type get_non_bool_value_type(const std::string& value) const;
};

} // Scripting
} // Koi

#endif //KOISCRIPT_LEXICON_HPP
