//
// Created by rfish on 7/10/2024.
//

#ifndef KOI_SCRIPTING_TOKEN_HPP
#define KOI_SCRIPTING_TOKEN_HPP


#include <string>
#include <utility>
#include <ostream>


namespace Koi { namespace Scripting {

struct Token {
public:
    enum Type : int {
        SCRIPTING_TOKEN_TYPE_INVALID = -1,
        SCRIPTING_TOKEN_TYPE_MIN = 0,
        SCRIPTING_TOKEN_TYPE_VALUE = SCRIPTING_TOKEN_TYPE_MIN,
        SCRIPTING_TOKEN_TYPE_BOOL,
        SCRIPTING_TOKEN_TYPE_INT,
        SCRIPTING_TOKEN_TYPE_FLOAT,
        SCRIPTING_TOKEN_TYPE_TEXT,
        SCRIPTING_TOKEN_TYPE_ID,
        SCRIPTING_TOKEN_TYPE_TYPE,
        SCRIPTING_TOKEN_TYPE_VAR_META,
        SCRIPTING_TOKEN_TYPE_FUN_META,
        SCRIPTING_TOKEN_TYPE_EXE_META,
        SCRIPTING_TOKEN_TYPE_VAL_META,
        SCRIPTING_TOKEN_TYPE_REF_META,
        SCRIPTING_TOKEN_TYPE_LIB_META,
        SCRIPTING_TOKEN_TYPE_IMP_META,
        SCRIPTING_TOKEN_TYPE_GROUPING_START,
        SCRIPTING_TOKEN_TYPE_GROUPING_END,
        SCRIPTING_TOKEN_TYPE_SCOPE_START,
        SCRIPTING_TOKEN_TYPE_SCOPE_END,
        SCRIPTING_TOKEN_TYPE_ID_START,
        SCRIPTING_TOKEN_TYPE_ID_END,
        SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START,
        SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END,
        SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND,
        SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND,
        SCRIPTING_TOKEN_TYPE_ASSIGNER,
        SCRIPTING_TOKEN_TYPE_COMBINER,
        SCRIPTING_TOKEN_TYPE_SEPARATOR,
        SCRIPTING_TOKEN_TYPE_DELIMITER,
        SCRIPTING_TOKEN_TYPE_RESULTER,
        SCRIPTING_TOKEN_TYPE_RESERVED_ID,
        SCRIPTING_TOKEN_TYPE_RESERVED_EOF,
        SCRIPTING_TOKEN_TYPE_SIZE
    };

    enum InternalType: int {
        SCRIPTING_TOKEN_INTERNAL_TYPE_INVALID = -1,
        SCRIPTING_TOKEN_INTERNAL_TYPE_MIN = 0,
        SCRIPTING_TOKEN_INTERNAL_TYPE_BOOL = SCRIPTING_TOKEN_INTERNAL_TYPE_MIN,
        SCRIPTING_TOKEN_INTERNAL_TYPE_INT,
        SCRIPTING_TOKEN_INTERNAL_TYPE_FLOAT,
        SCRIPTING_TOKEN_INTERNAL_TYPE_STRING,
        SCRIPTING_TOKEN_INTERNAL_TYPE_SIZE
    };


protected:
    Type _type = SCRIPTING_TOKEN_TYPE_INVALID;
    InternalType _internal_type = SCRIPTING_TOKEN_INTERNAL_TYPE_INVALID;

    unsigned int _string_size = 0u; // includes \0 terminator
    union {
        bool _value_bool = false;
        int _value_int;
        float _value_float;
        char* _value_string;
    };


public:
    static Token from(Type in_type, const char* in_value_string);
    static Token from(Type in_type, const std::string& in_value_string);

    Token() = default;
    Token(Type in_type, bool in_value);
    Token(Type in_type, int in_value);
    Token(Type in_type, float in_value);

    /**
     * @brief Constructor using c-string.
     * @remarks Defined to ensure compiler uses a string constructor when
     * passing in string literals, otherwise it implicitly casts to bool.
     * @param in_type
     * @param in_value
     */
    Token(Type in_type, const char* in_value);
    Token(Type in_type, const std::string& in_value);

    Token(const Token& rhs);
    Token(Token&& rhs) noexcept;

    virtual ~Token();

    Token& operator=(const Token& rhs);
    Token& operator=(Token&& rhs) noexcept;

    bool operator==(const Token& rhs) const;
    bool operator!=(const Token& rhs) const;

    explicit operator std::string() const;

    Type get_type() const;
    InternalType get_internal_type() const;
    bool get_value_bool() const;
    int get_value_int() const;
    float get_value_float() const;
    std::string get_value_string() const;

    friend std::ostream& operator<<(std::ostream& lhs, const Token& rhs);


protected:
    static std::string _get_name_of_type(Type in_type);
    static std::string _get_name_of_internal_type(InternalType in_internal_type);

    void _copy(const Token& rhs);
};


}
}


#endif //KOI_SCRIPTING_TOKEN_HPP
