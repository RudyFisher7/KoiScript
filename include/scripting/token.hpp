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


#ifndef KOI_SCRIPTING_TOKEN_HPP
#define KOI_SCRIPTING_TOKEN_HPP


#include <string>
#include <utility>
#include <ostream>


namespace Koi { namespace Scripting {

enum TokenType : int {
    TOKEN_TYPE_INVALID = -1,
    TOKEN_TYPE_MIN = 0,

    // statement starters
    TOKEN_TYPE_VAR = TOKEN_TYPE_MIN,
    TOKEN_TYPE_FUNC,
    TOKEN_TYPE_CLASS,

    // expression starter
    TOKEN_TYPE_IDENTIFIER,

    // delimiter/separator
    TOKEN_TYPE_DELIMITER,
    TOKEN_TYPE_SEPARATOR,

    // built-in class types
    TOKEN_TYPE_CLASS_OBJECT,
    TOKEN_TYPE_CLASS_BOOL,
    TOKEN_TYPE_CLASS_CHAR,
    TOKEN_TYPE_CLASS_NUMBER,
    TOKEN_TYPE_CLASS_INT,
    TOKEN_TYPE_CLASS_UINT,
    TOKEN_TYPE_CLASS_FLOAT,
    TOKEN_TYPE_CLASS_UFLOAT,
    TOKEN_TYPE_CLASS_STRING,

    // bookends
    TOKEN_TYPE_STRING_LITERAL_BOOKEND,

    // generics
    TOKEN_TYPE_GENERIC_START,
    TOKEN_TYPE_GENERIC_END,

    // operators
    TOKEN_TYPE_OPERATOR_MEMBER_ACCESS,
    TOKEN_TYPE_OPERATOR_INHERITANCE,
    TOKEN_TYPE_OPERATOR_SCOPE,
    TOKEN_TYPE_OPERATOR_REFERENCE,
    TOKEN_TYPE_OPERATOR_RETURN,

    // special
    TOKEN_TYPE_EOF,
    TOKEN_TYPE_SIZE
};

struct Token {
    const char* text;
    TokenType type;
    const char* file_path;
    const unsigned long line_number;
    const unsigned long column_number;
};

//struct Token {
//public:
//    enum Type : int {
//        SCRIPTING_TOKEN_TYPE_INVALID = -1,
//        SCRIPTING_TOKEN_TYPE_MIN = 0,
//        SCRIPTING_TOKEN_TYPE_LITERAL_BOOL_FALSE = SCRIPTING_TOKEN_TYPE_MIN,
//        SCRIPTING_TOKEN_TYPE_LITERAL_BOOL_TRUE,
//        SCRIPTING_TOKEN_TYPE_LITERAL_CHAR,
//        SCRIPTING_TOKEN_TYPE_LITERAL_INT,
//        SCRIPTING_TOKEN_TYPE_LITERAL_FLOAT,
//        SCRIPTING_TOKEN_TYPE_LITERAL_STRING,
//        SCRIPTING_TOKEN_TYPE_BUILT_IN_TYPE_BOOL,
//        SCRIPTING_TOKEN_TYPE_BUILT_IN_TYPE_CHAR,
//        SCRIPTING_TOKEN_TYPE_BUILT_IN_TYPE_INT,
//        SCRIPTING_TOKEN_TYPE_BUILT_IN_TYPE_FLOAT,
//        SCRIPTING_TOKEN_TYPE_BUILT_IN_TYPE_STRING,
//        SCRIPTING_TOKEN_TYPE_BUILT_IN_TYPE_OBJECT,
//        SCRIPTING_TOKEN_TYPE_GROUPING_START,
//        SCRIPTING_TOKEN_TYPE_GROUPING_END,
//        SCRIPTING_TOKEN_TYPE_SCOPE_START,
//        SCRIPTING_TOKEN_TYPE_SCOPE_END,
//        SCRIPTING_TOKEN_TYPE_TEMPLATE_START,
//        SCRIPTING_TOKEN_TYPE_TEMPLATE_END,
//        SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND,
//        SCRIPTING_TOKEN_TYPE_LITERAL_STRING_BOOKEND,
//        SCRIPTING_TOKEN_TYPE_OPERATOR_REFERENCE,
//        SCRIPTING_TOKEN_TYPE_OPERATOR_MEMBER_ACCESS,
//        SCRIPTING_TOKEN_TYPE_OPERATOR_RETURN,
//        SCRIPTING_TOKEN_TYPE_OPERATOR_INHERITANCE,
//        SCRIPTING_TOKEN_TYPE_OPERATOR_SCOPE,
//        SCRIPTING_TOKEN_TYPE_SEPARATOR,
//        SCRIPTING_TOKEN_TYPE_DELIMITER,
//        SCRIPTING_TOKEN_TYPE_IDENTIFIER,
//        SCRIPTING_TOKEN_TYPE_CLASS,
//        SCRIPTING_TOKEN_TYPE_LIBRARY,
//        SCRIPTING_TOKEN_TYPE_IMPORT,
//        SCRIPTING_TOKEN_TYPE_EOF,
//        SCRIPTING_TOKEN_TYPE_SIZE
//    };
//
//    enum InternalType: int {
//        SCRIPTING_TOKEN_INTERNAL_TYPE_INVALID = -1,
//        SCRIPTING_TOKEN_INTERNAL_TYPE_MIN = 0,
//        SCRIPTING_TOKEN_INTERNAL_TYPE_BOOL = SCRIPTING_TOKEN_INTERNAL_TYPE_MIN,
//        SCRIPTING_TOKEN_INTERNAL_TYPE_INT,
//        SCRIPTING_TOKEN_INTERNAL_TYPE_FLOAT,
//        SCRIPTING_TOKEN_INTERNAL_TYPE_STRING,
//        SCRIPTING_TOKEN_INTERNAL_TYPE_SIZE
//    };
//
//
//protected:
//    static const char* TRUE_BOOL;
//    Type _type = SCRIPTING_TOKEN_TYPE_INVALID;
//    InternalType _internal_type = SCRIPTING_TOKEN_INTERNAL_TYPE_INVALID;
//
//    unsigned int _string_size = 0u; // includes \0 terminator
//    union {
//        bool _value_bool = false;
//        int _value_int;
//        float _value_float;
//        char* _value_string;
//    };
//
//
//public:
//    static Token from(Type in_type, const char* in_value_string);
//    static Token from(Type in_type, const std::string& in_value_string);
//
//    Token() = default;
//    Token(Type in_type, bool in_value);
//    Token(Type in_type, int in_value);
//    Token(Type in_type, float in_value);
//
//    /**
//     * @brief Constructor using c-string.
//     * @remarks Defined to ensure compiler uses a string constructor when
//     * passing in string literals, otherwise it implicitly casts to bool.
//     * @param in_type
//     * @param in_value
//     */
//    Token(Type in_type, const char* in_value);
//    Token(Type in_type, const std::string& in_value);
//
//    Token(const Token& rhs);
//    Token(Token&& rhs) noexcept;
//
//    virtual ~Token();
//
//    Token& operator=(const Token& rhs);
//    Token& operator=(Token&& rhs) noexcept;
//
//    bool operator==(const Token& rhs) const;
//    bool operator!=(const Token& rhs) const;
//
//    explicit operator std::string() const;
//
//    Type get_type() const;
//    InternalType get_internal_type() const;
//    bool get_value_bool() const;
//    int get_value_int() const;
//    float get_value_float() const;
//    std::string get_value_string() const;
//
//    //fixme:: conform to std::string operator
//    friend std::ostream& operator<<(std::ostream& lhs, const Token& rhs);
//
//
//protected:
//    static std::string _get_name_of_type(Type in_type);
//    static std::string _get_name_of_internal_type(InternalType in_internal_type);
//
//    void _copy(const Token& rhs);
//};


}
}


#endif //KOI_SCRIPTING_TOKEN_HPP
