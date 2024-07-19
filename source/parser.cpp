//
// Created by rfish on 7/11/2024.
//


#include "scripting/parser.hpp"

#include "scripting/log/log.hpp"

#include <memory>


namespace Koi {
namespace Scripting {
const unsigned int Parser::MIN_VALID_EVAL_META_SIZE = 6u;
const std::string Parser::MAIN_ENTRY_POINT_KEY("main");

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


bool Parser::_is_main_exe_valid(
        std::vector<Token>::const_iterator& it,
        std::vector<Token>::const_iterator& end
) const {
    bool result = false;

    result = (
            it != end
            && it->get_type() == Token::SCRIPTING_TOKEN_TYPE_EXE_META
    );

    result = (
            result
            && _are_enough_tokens_left(it, end, MIN_VALID_EVAL_META_SIZE)
            && (it + 2u)->get_value_string() == MAIN_ENTRY_POINT_KEY
    );

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
            bool has_more_args = it->get_type() != Token::SCRIPTING_TOKEN_TYPE_GROUPING_END;
            while(it != end && result == SCRIPTING_PARSER_ERROR_OK && has_more_args) {
                std::shared_ptr<AstNode> arg;
                result = _parse_arg(it, end, arg);

                // iterate past any trailing separator token
                if (it != end && it->get_type() == Token::SCRIPTING_TOKEN_TYPE_SEPARATOR) {
                    ++it;
                }

                if (it != end) {
                    has_more_args = it->get_type() != Token::SCRIPTING_TOKEN_TYPE_GROUPING_END;
                }
            }

            is_valid = result == SCRIPTING_PARSER_ERROR_OK && !has_more_args;
            KOI_LOG_IF_NOT(
                    is_valid,
                    std::string("Error while parsing exe args. result=")
                    + std::to_string(result)
                    + std::string(", has more args=")
                    + std::to_string(has_more_args)
            );

            ++it;
        }

        is_valid = is_valid && it != end;
        KOI_LOG_IF_NOT(is_valid, "EOF reached before finding a delimiter for exe meta.");

        if (is_valid) {
            is_valid = it->get_type() == Token::SCRIPTING_TOKEN_TYPE_DELIMITER;
            KOI_LOG_IF_NOT(is_valid, "No delimiter found for exe meta.");
        }

        if (is_valid) {
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
    Error result = SCRIPTING_PARSER_ERROR_OK;

    it += 2u;

    return result;
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