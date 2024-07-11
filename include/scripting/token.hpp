//
// Created by rfish on 7/10/2024.
//

#ifndef KOI_SCRIPTING_TOKEN_HPP
#define KOI_SCRIPTING_TOKEN_HPP


#include <utility>

#include "scripting/variant.hpp"


namespace Koi { namespace Scripting {

struct Token {
public:
    enum Type : int {
        SCRIPTING_TOKEN_TYPE_INVALID = -1,
        SCRIPTING_TOKEN_TYPE_MIN = 0,
        SCRIPTING_TOKEN_TYPE_VALUE = SCRIPTING_TOKEN_TYPE_MIN,
        SCRIPTING_TOKEN_TYPE_TYPE,
        SCRIPTING_TOKEN_TYPE_IDENTIFIER,
        SCRIPTING_TOKEN_TYPE_GROUPING_START,
        SCRIPTING_TOKEN_TYPE_GROUPING_END,
        SCRIPTING_TOKEN_TYPE_SCOPE_START,
        SCRIPTING_TOKEN_TYPE_SCOPE_END,
        SCRIPTING_TOKEN_TYPE_VALUE_START,
        SCRIPTING_TOKEN_TYPE_VALUE_END,
        SCRIPTING_TOKEN_TYPE_DELIMITER,
        SCRIPTING_TOKEN_TYPE_FUNCTION_BODY_START,
        SCRIPTING_TOKEN_TYPE_ASSIGNER,
        SCRIPTING_TOKEN_TYPE_RESULTER,
        SCRIPTING_TOKEN_TYPE_SIZE
    };

    Type type = SCRIPTING_TOKEN_TYPE_VALUE;
    Variant value;

    Token() = default;
    Token(Type in_type, Variant in_value);

    Token(const Token& rhs) = default;
    Token(Token&& rhs) = default;

    virtual ~Token() = default;

    Token& operator=(const Token& rhs) = default;
    Token& operator=(Token&& rhs) = default;
};

}
}


#endif //KOI_SCRIPTING_TOKEN_HPP
