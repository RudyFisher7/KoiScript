//
// Created by rfish on 7/11/2024.
//


#ifndef KOI_SCRIPTING_PARSER_HPP
#define KOI_SCRIPTING_PARSER_HPP


#include "scripting/ast_node.hpp"
#include "scripting/token.hpp"

#include <vector>


namespace Koi { namespace Scripting {

class Parser {
public:
    enum Error : int {
        SCRIPTING_PARSER_ERROR_MIN = 0,
        SCRIPTING_PARSER_ERROR_OK = SCRIPTING_PARSER_ERROR_MIN,
        SCRIPTING_PARSER_ERROR_SIZE
    };


    Error parse(const std::vector<Token>& tokens, AstNode** out_ast);

protected:
    //

};

} // Scripting
} // Koi


#endif //KOI_SCRIPTING_PARSER_HPP
