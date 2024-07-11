//
// Created by rfish on 7/10/2024.
//


#include "../include/scripting/token.hpp"


namespace Koi { namespace Scripting {

Token::Token(Type in_type, Variant  in_value) : type(in_type), value(std::move(in_value)) {

}

}
}
