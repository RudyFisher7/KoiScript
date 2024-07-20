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


Parser::Error Parser::_parse_ret_statement(
        std::vector<Token>::const_iterator& it,
        const std::vector<Token>::const_iterator& end,
        std::shared_ptr<FunctionLiteral>& out_current_ast
) const {
    Error result = SCRIPTING_PARSER_ERROR_OK;


    if (
            it->get_type() == Token::SCRIPTING_TOKEN_TYPE_RESULTER
            && (it + 1u)->get_type() == Token::SCRIPTING_TOKEN_TYPE_COMBINER
    ) {
        it += 2u;
        if (_is_variable_literal(it->get_type())) {
            std::shared_ptr<VariableLiteral> variable_literal;
            result = _parse_variable_literal(it, end, variable_literal);
            out_current_ast->return_statement = variable_literal;
            if (it->get_type() == Token::SCRIPTING_TOKEN_TYPE_DELIMITER) {
                ++it;
            } else {
                //todo:: error handling
            }
        } else {
            std::shared_ptr<AstNode> statement;
            result = _parse_statement(it, end, statement);
            out_current_ast->return_statement = statement;
        }
    }

    return result;
}


Parser::Error Parser::_parse_statement(
        std::vector<Token>::const_iterator& it,
        const std::vector<Token>::const_iterator& end,
        std::shared_ptr<AstNode>& out_current_ast
) const {
    Error result = SCRIPTING_PARSER_ERROR_OK;

    switch (it->get_type()) {
        case Token::SCRIPTING_TOKEN_TYPE_VAR_META:
            break;
        case Token::SCRIPTING_TOKEN_TYPE_FUN_META:
            break;
        case Token::SCRIPTING_TOKEN_TYPE_EXE_META:
            result = _parse_exe(it, end, out_current_ast);
            break;
        case Token::SCRIPTING_TOKEN_TYPE_VAL_META:
            break;
        case Token::SCRIPTING_TOKEN_TYPE_REF_META:
            break;
        case Token::SCRIPTING_TOKEN_TYPE_LIB_META:
            break;
        case Token::SCRIPTING_TOKEN_TYPE_IMP_META:
            break;
        default:
            break;
    }

    return result;
}


Parser::Error Parser::_parse_exe(
        std::vector<Token>::const_iterator& it,
        const std::vector<Token>::const_iterator& end,
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

                if (arg) {
                    exe->args.emplace_back(arg);
                }

                // iterate past any trailing separator token
                if (it != end && it->get_type() == Token::SCRIPTING_TOKEN_TYPE_SEPARATOR) {
                    ++it;
                }

                if (it != end) {//fixme:: can use a token type EOF as cases rather than keep using this check
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
            ++it;
            KOI_LOG_IF_NOT(is_valid, "No delimiter found for exe meta.");
        }

        out_current_ast = exe;
    }

    if (!is_valid) {
        result = SCRIPTING_PARSER_ERROR_INVALID_EVALUATION_META;
    }

    return result;
}


Parser::Error Parser::_parse_arg(
        std::vector<Token>::const_iterator& it,
        const std::vector<Token>::const_iterator& end,
        std::shared_ptr<AstNode>& out_current_ast
) const {
    Error result = SCRIPTING_PARSER_ERROR_OK;

    switch (it->get_type()) {
        case Token::SCRIPTING_TOKEN_TYPE_BOOL:
        case Token::SCRIPTING_TOKEN_TYPE_INT:
        case Token::SCRIPTING_TOKEN_TYPE_FLOAT:
//        case Token::SCRIPTING_TOKEN_TYPE_TEXT://note: text starts with verbatim bookend
        case Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND: { // handles text literal
            std::shared_ptr<VariableLiteral> variable_literal;
            result = _parse_variable_literal(it, end, variable_literal);
            out_current_ast = variable_literal;
        }
            break;
        case Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_VOID: {
            std::shared_ptr<FunctionLiteral> function_literal;
            result = _parse_function_literal(it, end, function_literal);
            out_current_ast = function_literal;
        }
            break;
        case Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL:
        case Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_INT:
        case Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_FLOAT:
        case Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_TEXT:
            result = _parse_typed_literal(it, end, out_current_ast);
            break;
        case Token::SCRIPTING_TOKEN_TYPE_EXE_META:
            result = _parse_exe(it, end, out_current_ast);
            break;
        case Token::SCRIPTING_TOKEN_TYPE_VAL_META:
            break;
        case Token::SCRIPTING_TOKEN_TYPE_REF_META:
            break;
        default:
            result = SCRIPTING_PARSER_ERROR_INVALID_TOKEN_IN_META_ARG;
            KOI_LOG("Invalid token in meta arg.");
            break;
    }

    return result;
}


Parser::Error Parser::_parse_typed_literal(
        std::vector<Token>::const_iterator& it,
        const std::vector<Token>::const_iterator& end,
        std::shared_ptr<AstNode>& out_current_ast
) const {
    Error result = SCRIPTING_PARSER_ERROR_OK;
    unsigned int distance = 0u;
    if (_find_next_token_of_type(it, end, Token::SCRIPTING_TOKEN_TYPE_COMBINER, distance)) {

        // type is basic; literal is a variable
        if (distance == 1u) {
            it += 2u;
            std::shared_ptr<VariableLiteral> variable_literal;
            result = _parse_variable_literal(it, end, variable_literal);
            bool types_match = _do_basic_types_match((it - 2u)->get_type(), variable_literal->value.get_type());

        } else { // type is complex; literal is either a function or an array
            Type type(_get_basic_type_from(it->get_type()));

            ++it;
            unsigned int i = 1u;
            while (
                    i < distance
                    && it->get_type() != Token::SCRIPTING_TOKEN_TYPE_GROUPING_START
                    && result == SCRIPTING_PARSER_ERROR_OK
            ) {
                if (it->get_type() == Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START) {
                    if ((it + 1u)->get_type() == Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END) {
                        ++type.array_dimensions;
                        it += 2u;
                        i += 2u;
                    }
                }
            }

            std::shared_ptr<FunctionLiteral> function_literal = std::make_shared<FunctionLiteral>(type);

            if (it->get_type() == Token::SCRIPTING_TOKEN_TYPE_GROUPING_START) {
                ++it;
                while (i < distance && result == SCRIPTING_PARSER_ERROR_OK) {
                    switch (it->get_type()) {
                        case Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL:
                        case Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_INT:
                        case Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_FLOAT:
                        case Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_TEXT:
                            type.parameter_types.emplace_back(_get_basic_type_from(it->get_type()));
                            ++it;
                            ++i;
                            break;
                        case Token::SCRIPTING_TOKEN_TYPE_GROUPING_END: //fixme:: support nested function types
                            ++i;
                            ++it;
                            if (i != distance - 1u) {
                                result = SCRIPTING_PARSER_ERROR_INVALID_TYPE_SPECIFIER;
                                KOI_LOG("Invalid type specifier.");
                            }
                            break;
                        default:
                            result = SCRIPTING_PARSER_ERROR_INVALID_TYPE_SPECIFIER;
                            KOI_LOG("Invalid type specifier.");
                            break;
                    }

                    ++it;
                    ++i;
                }

                if (result == SCRIPTING_PARSER_ERROR_OK) {
                    result = _parse_function_literal(it, end, function_literal);
                    out_current_ast = function_literal;
                }
            } else {
                //todo:: this is an array type
            }
        }
    } else {
        result = SCRIPTING_PARSER_ERROR_INVALID_TYPE_SPECIFIER;
        KOI_LOG("Invalid type specifier.");
    }

    return result;
}


Parser::Error Parser::_parse_function_literal(
        std::vector<Token>::const_iterator& it,
        const std::vector<Token>::const_iterator& end,
        std::shared_ptr<FunctionLiteral>& out_current_ast
) const {
    Error result = SCRIPTING_PARSER_ERROR_OK;

    if (it->get_type() == Token::SCRIPTING_TOKEN_TYPE_SCOPE_START) {
        ++it;

        while (
                result == SCRIPTING_PARSER_ERROR_OK
                && it->get_type() != Token::SCRIPTING_TOKEN_TYPE_RESULTER
                && it->get_type() != Token::SCRIPTING_TOKEN_TYPE_SCOPE_END
        ) {
            std::shared_ptr<AstNode> statement;
            result = _parse_statement(it, end, statement);
            out_current_ast->statements.emplace_back(statement);
        }

        if (out_current_ast->type.return_type != SCRIPTING_BASIC_TYPE_VOID) {
            result = _parse_ret_statement(it, end, out_current_ast);
        }

        if (it->get_type() == Token::SCRIPTING_TOKEN_TYPE_SCOPE_END) {
            ++it;
        }
    }

    return result;
}


Parser::Error Parser::_parse_array_literal(
        std::vector<Token>::const_iterator& it,
        const std::vector<Token>::const_iterator& end,
        std::shared_ptr<AstNode>& out_current_ast
) const {
    Error result = SCRIPTING_PARSER_ERROR_OK;
    return result;
}


Parser::Error Parser::_parse_variable_literal(
        std::vector<Token>::const_iterator& it,
        const std::vector<Token>::const_iterator& end,
        std::shared_ptr<VariableLiteral>& out_current_ast
) const {
    Error result = SCRIPTING_PARSER_ERROR_OK;

    std::vector<Token>::const_iterator var_lit_token = it;

    if (it->get_type() == Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND) {
        var_lit_token = ++it;
    }

    switch (var_lit_token->get_type()) {
        case Token::SCRIPTING_TOKEN_TYPE_BOOL:
            out_current_ast = std::make_shared<VariableLiteral>(var_lit_token->get_value_bool());
            break;
        case Token::SCRIPTING_TOKEN_TYPE_INT:
            out_current_ast = std::make_shared<VariableLiteral>(var_lit_token->get_value_int());
            break;
        case Token::SCRIPTING_TOKEN_TYPE_FLOAT:
            out_current_ast = std::make_shared<VariableLiteral>(var_lit_token->get_value_float());
            break;
        case Token::SCRIPTING_TOKEN_TYPE_TEXT:
            out_current_ast = std::make_shared<VariableLiteral>(var_lit_token->get_value_string());
            break;
        default:
            result = SCRIPTING_PARSER_ERROR_INVALID_VARIABLE_LITERAL;
            break;
    }

    if (result == SCRIPTING_PARSER_ERROR_OK) {
        ++it;

        switch (it->get_type()) {
            case Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND:
                ++it;
                break;
            case Token::SCRIPTING_TOKEN_TYPE_EOF:
                result = SCRIPTING_PARSER_ERROR_UNEXPECTED_END_OF_TOKENS;
                break;
            default:
                // pass through, still valid
                break;
        }
    }

    KOI_LOG_IF_NOT(
            result == SCRIPTING_PARSER_ERROR_OK,
            "Error parsing variable literal. error=" + std::to_string(result)
    );

    return result;
}


bool Parser::_is_main_exe_valid(
        std::vector<Token>::const_iterator& it,
        const std::vector<Token>::const_iterator& end
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


bool Parser::_find_next_token_of_type(
        std::vector<Token>::const_iterator it,
        std::vector<Token>::const_iterator end,
        Token::Type token_type,
        unsigned int& out_distance
) const {
    bool result = 0u;
    unsigned int i = 0u;

    if (out_distance == 0u) {
        while (!result && it < end) {
            result = it->get_type() == token_type;

            if (!result) {
                ++it;
                ++i;
            }
        }
    } else {
        while (!result && i < out_distance && it < end) {
            result = it->get_type() == token_type;

            if (!result) {
                ++it;
                ++i;
            }
        }
    }

    out_distance = i;

    return result;
}


bool Parser::_is_variable_literal(Token::Type type) const {
    bool result = false;

    switch (type) {
        case Token::SCRIPTING_TOKEN_TYPE_BOOL:
        case Token::SCRIPTING_TOKEN_TYPE_INT:
        case Token::SCRIPTING_TOKEN_TYPE_FLOAT:
        case Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND:
            result = true;
            break;
        default:
            // just pass through with false
            break;
    }

    return result;
}


bool Parser::_do_basic_types_match(Token::Type token_type, Variant::Type variant_type) const {
    bool result = false;

    switch (variant_type) {
        case Variant::SCRIPTING_VARIANT_TYPE_VOID:
            result = token_type == Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_VOID;
            break;
        case Variant::SCRIPTING_VARIANT_TYPE_BOOL:
            result = token_type == Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL;
            break;
        case Variant::SCRIPTING_VARIANT_TYPE_INT:
            result = token_type == Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_INT;
            break;
        case Variant::SCRIPTING_VARIANT_TYPE_FLOAT:
            result = token_type == Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_FLOAT;
            break;
        case Variant::SCRIPTING_VARIANT_TYPE_TEXT:
            result = token_type == Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_TEXT;
            break;
        case Variant::SCRIPTING_VARIANT_TYPE_REF:
            //fixme:: implement
            KOI_LOG("Reference types aren't implemented yet.");
            break;
        default:
            // just pass through with false
            break;
    }

    return result;
}


bool Parser::_do_basic_types_match(Token::Type token_type, BasicType basic_type) const {
    bool result = false;

    switch (basic_type) {
        case SCRIPTING_BASIC_TYPE_VOID:
            result = token_type == Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_VOID;
            break;
        case SCRIPTING_BASIC_TYPE_BOOL:
            result = token_type == Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL;
            break;
        case SCRIPTING_BASIC_TYPE_INT:
            result = token_type == Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_INT;
            break;
        case SCRIPTING_BASIC_TYPE_FLOAT:
            result = token_type == Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_FLOAT;
            break;
        case SCRIPTING_BASIC_TYPE_TEXT:
            result = token_type == Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_TEXT;
            break;
        case SCRIPTING_BASIC_TYPE_REF:
            //fixme:: implement
            KOI_LOG("Reference types aren't implemented yet.");
            break;
        default:
            // just pass through with false
            break;
    }

    return result;
}


BasicType Parser::_get_basic_type_from(Token::Type token_type) const {
    BasicType result = SCRIPTING_BASIC_TYPE_INVALID;

    switch (token_type) {
        case Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_VOID:
            result = SCRIPTING_BASIC_TYPE_VOID;
            break;
        case Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL:
            result = SCRIPTING_BASIC_TYPE_BOOL;
            break;
        case Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_INT:
            result = SCRIPTING_BASIC_TYPE_INT;
            break;
        case Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_FLOAT:
            result = SCRIPTING_BASIC_TYPE_FLOAT;
            break;
        case Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_TEXT:
            result = SCRIPTING_BASIC_TYPE_TEXT;
            break;
        default:
            // just pass through with false
            break;
    }

    return result;
}

} // Scripting
} // Koi
