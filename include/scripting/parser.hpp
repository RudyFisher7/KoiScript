/*
 * MIT License
 *
 * Copyright (c) 2024 kiyasui-hito
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#ifndef KOI_SCRIPTING_PARSER_HPP
#define KOI_SCRIPTING_PARSER_HPP


#include "scripting/abstract_syntax_tree/node.hpp"
#include "scripting/abstract_syntax_tree/meta.hpp"
#include "scripting/abstract_syntax_tree/literal.hpp"
#include "scripting/token.hpp"

#include <memory>
#include <vector>


namespace Koi { namespace Scripting {

class Parser {
public:
    enum Error : int {
        SCRIPTING_PARSER_ERROR_MIN = 0,
        SCRIPTING_PARSER_ERROR_OK = SCRIPTING_PARSER_ERROR_MIN,
        SCRIPTING_PARSER_ERROR_INVALID_EVALUATION_META,
        SCRIPTING_PARSER_ERROR_INVALID_TOKEN_IN_META_ARG,
        SCRIPTING_PARSER_ERROR_INVALID_TYPE_SPECIFIER,
        SCRIPTING_PARSER_ERROR_INVALID_VARIABLE_LITERAL,
        SCRIPTING_PARSER_ERROR_UNEXPECTED_END_OF_TOKENS,
        SCRIPTING_PARSER_ERROR_SIZE
    };


protected:
    static const unsigned int MIN_VALID_EVAL_META_SIZE;
    static const std::string MAIN_ENTRY_POINT_KEY;

public:
    Error parse(const std::vector<Token>& tokens, std::shared_ptr<Ast::Node>& out_ast);


protected:
    Error _parse_ret_statement(
            std::vector<Token>::const_iterator& it,
            const std::vector<Token>::const_iterator& end,
            std::shared_ptr<Ast::FunctionLiteral>& out_current_ast
    ) const;


    Error _parse_statement(
            std::vector<Token>::const_iterator& it,
            const std::vector<Token>::const_iterator& end,
            std::shared_ptr<Ast::Statement>& out_current_ast
    ) const;

    Error _parse_exe(
            std::vector<Token>::const_iterator& it,
            const std::vector<Token>::const_iterator& end,
            std::shared_ptr<Ast::ExecuteMeta>& out_current_ast
    ) const;

    //todo:: implement
    Error _parse_arg(
            std::vector<Token>::const_iterator& it,
            const std::vector<Token>::const_iterator& end,
            std::shared_ptr<Ast::Expression>& out_current_ast
    ) const;


    Error _parse_typed_literal(
            std::vector<Token>::const_iterator& it,
            const std::vector<Token>::const_iterator& end,
            std::shared_ptr<Ast::Literal>& out_current_ast
    ) const;


    Error _parse_function_literal(
            std::vector<Token>::const_iterator& it,
            const std::vector<Token>::const_iterator& end,
            std::shared_ptr<Ast::FunctionLiteral>& out_current_ast
    ) const;


    Error _parse_array_literal(
            std::vector<Token>::const_iterator& it,
            const std::vector<Token>::const_iterator& end,
            std::shared_ptr<Ast::Node>& out_current_ast
    ) const;


    Error _parse_variable_literal(
            std::vector<Token>::const_iterator& it,
            const std::vector<Token>::const_iterator& end,
            std::shared_ptr<Ast::VariableLiteral>& out_current_ast
    ) const;


    bool _is_main_exe_valid(
            std::vector<Token>::const_iterator& it,
            const std::vector<Token>::const_iterator& end
    ) const;


    bool _are_enough_tokens_left(
            std::vector<Token>::const_iterator it,
            std::vector<Token>::const_iterator end,
            unsigned int size
    ) const;


    bool _find_next_token_of_type(
            std::vector<Token>::const_iterator it,
            std::vector<Token>::const_iterator end,
            Token::Type token_type,
            unsigned int& out_distance
    ) const;

    bool _is_variable_literal(Token::Type type) const;


    //fixme:: implement ref types
    bool _do_basic_types_match(Token::Type token_type, BasicType variant_type) const;
    BasicType _get_basic_type_from(Token::Type token_type) const;

};

} // Scripting
} // Koi


#endif //KOI_SCRIPTING_PARSER_HPP
