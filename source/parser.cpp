//
// Created by rfish on 7/11/2024.
//


#include "scripting/parser.hpp"

#include "scripting/log/log.hpp"

#include <memory>


namespace Koi {
namespace Scripting {
const unsigned int Parser::MIN_VALID_EVAL_META_SIZE = 6u;

Parser::Error Parser::parse(const std::vector<Token>& tokens, std::shared_ptr<AstNode>& out_ast) {
    Error result = SCRIPTING_PARSER_ERROR_OK;

    //todo::
    // 1. build out ast
    // 2. register ids from declarations found in program

    //fixme:: validate that exe<main>({}); is the first few tokens

    auto it = tokens.cbegin();
    auto end = tokens.cend();


    if (_is_main_exe_valid(it, end)) {
        result = _parse_exe(it, end, out_ast);
    }

    return result;
}


bool Parser::_is_main_exe_valid(std::vector<Token>::const_iterator& it, std::vector<Token>::const_iterator& end) const {
    bool result = false;

    result = (
            it != end
            && it->get_type() == Token::SCRIPTING_TOKEN_TYPE_EXE_META
    );

    result = result && _are_enough_tokens_left(it, end, MIN_VALID_EVAL_META_SIZE);

    return result;
}


Parser::Error Parser::_parse_exe(
        std::vector<Token>::const_iterator& it,
        std::vector<Token>::const_iterator& end,
        std::shared_ptr<AstNode>& out_current_ast
) const {
    Error result = SCRIPTING_PARSER_ERROR_OK;
    bool is_valid = false;

    is_valid = _are_enough_tokens_left(it, end, MIN_VALID_EVAL_META_SIZE);
    KOI_LOG_IF_NOT(is_valid, "Too few tokens for exe meta.");

    if (is_valid) {
        std::shared_ptr<Execute> exe = std::make_shared<Execute>();
        it += 2u;

        is_valid = it->get_type() == Token::SCRIPTING_TOKEN_TYPE_ID;
        KOI_LOG_IF_NOT(is_valid, "No id token for exe meta.");
        if (is_valid) {
            exe->executing_key = it->get_value_string();
        }

        it += 3u;

        if (is_valid) {
            //todo:: result = _parse_args
        }

        if (is_valid && result == SCRIPTING_PARSER_ERROR_OK) {
            out_current_ast = exe;
        }
    }

    if (!is_valid) {
        result = SCRIPTING_PARSER_ERROR_INVALID_EVALUATION_META;
    }

    return result;
}


Parser::Error Parser::_parse_arg(
        std::vector<Token>::const_iterator& it,
        std::vector<Token>::const_iterator& end,
        std::shared_ptr<AstNode>& out_current_ast
) const {
    return Parser::SCRIPTING_PARSER_ERROR_MIN;
}


bool Parser::_are_enough_tokens_left(
        std::vector<Token>::const_iterator it,
        std::vector<Token>::const_iterator end,
        unsigned int size
) const {
    bool result = false;

    unsigned int i = 0u;
    while (it != end && i < size) {
        ++it;
        ++i;
    }

    result = i == MIN_VALID_EVAL_META_SIZE;

    return result;
}

} // Scripting
} // Koi