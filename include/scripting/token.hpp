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
        SCRIPTING_TOKEN_TYPE_ID,
        SCRIPTING_TOKEN_TYPE_ARRAY_SIZE,
        SCRIPTING_TOKEN_TYPE_TYPE,
        SCRIPTING_TOKEN_TYPE_LEFT_META,
        SCRIPTING_TOKEN_TYPE_RIGHT_META,
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
        SCRIPTING_TOKEN_TYPE_SIZE
    };

    Type type = SCRIPTING_TOKEN_TYPE_VALUE;
    std::string value;

    Token() = default;
    Token(Type in_type, const std::string& in_value);

    Token(const Token& rhs) = default;
    Token(Token&& rhs) noexcept = default;

    virtual ~Token() = default;

    Token& operator=(const Token& rhs) = default;
    Token& operator=(Token&& rhs) noexcept = default;

    bool operator==(const Token& rhs) const;
    bool operator!=(const Token& rhs) const;

    friend std::ostream& operator<<(std::ostream& lhs, const Token& rhs);


protected:
    static std::string _get_name_of_type(Type in_type);
};


}
}


#endif //KOI_SCRIPTING_TOKEN_HPP
