//
// Created by rfish on 7/10/2024.
//


#include "../include/scripting/token.hpp"


#define NAMEOF(arg) #arg


namespace Koi { namespace Scripting {

Token::Token(Type in_type, const std::string&  in_value) : type(in_type), value(in_value) {

}


std::string Token::_get_name_of_type(Token::Type in_type) {
    std::string result;

    switch (in_type) {

        case SCRIPTING_TOKEN_TYPE_INVALID:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_INVALID);
            break;
        case SCRIPTING_TOKEN_TYPE_VALUE:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_VALUE);
            break;
        case SCRIPTING_TOKEN_TYPE_TYPE:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_TYPE);
            break;
        case SCRIPTING_TOKEN_TYPE_LEFT_META:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_LEFT_META);
            break;
        case SCRIPTING_TOKEN_TYPE_RIGHT_META:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_RIGHT_META);
            break;
        case SCRIPTING_TOKEN_TYPE_GROUPING_START:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_GROUPING_START);
            break;
        case SCRIPTING_TOKEN_TYPE_GROUPING_END:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_GROUPING_END);
            break;
        case SCRIPTING_TOKEN_TYPE_SCOPE_START:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_SCOPE_START);
            break;
        case SCRIPTING_TOKEN_TYPE_SCOPE_END:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_SCOPE_END);
            break;
        case SCRIPTING_TOKEN_TYPE_ID_START:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_ID_START);
            break;
        case SCRIPTING_TOKEN_TYPE_ID_END:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_ID_END);
            break;
        case SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND);
            break;
        case SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND);
            break;
        case SCRIPTING_TOKEN_TYPE_COMBINER:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_COMBINER);
            break;
        case SCRIPTING_TOKEN_TYPE_ASSIGNER:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_ASSIGNER);
            break;
        case SCRIPTING_TOKEN_TYPE_DELIMITER:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_DELIMITER);
            break;
        case SCRIPTING_TOKEN_TYPE_RESULTER:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_RESULTER);
            break;
        case SCRIPTING_TOKEN_TYPE_SIZE:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_SIZE);
            break;
        default:
            result = "Unknown. How did you do this?";
            break;
    }

    return result;
}


bool Token::operator==(const Token& rhs) const {
    return (
            type == rhs.type
            && value == rhs.value
    );
}


bool Token::operator!=(const Token& rhs) const {
    return !(*this == rhs);
}


std::ostream& operator<<(std::ostream& lhs, const Token& rhs) {
    lhs << "Token({value: " << rhs.value << ", type: " << Token::_get_name_of_type(rhs.type) << "})";

    return lhs;
}

}
}
