//
// Created by rfish on 7/11/2024.
//


#include "scripting/parser.hpp"


namespace Koi {
namespace Scripting {

Parser::Error Parser::parse(const std::vector<Token>& tokens, AstNode** out_ast) {
    Error result = SCRIPTING_PARSER_ERROR_OK;

    //fixme:: validate that exe<main>({}); is the first few tokens
    *out_ast = new Execute(0u);
    AstNode* root = *out_ast;


    return result;
}

} // Scripting
} // Koi