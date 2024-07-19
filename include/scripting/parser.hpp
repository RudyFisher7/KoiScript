//
// Created by rfish on 7/11/2024.
//


#ifndef KOI_SCRIPTING_PARSER_HPP
#define KOI_SCRIPTING_PARSER_HPP


#include "scripting/ast_node.hpp"
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
        SCRIPTING_PARSER_ERROR_SIZE
    };


protected:
    static const unsigned int MIN_VALID_EVAL_META_SIZE;

public:
    Error parse(const std::vector<Token>& tokens, std::shared_ptr<AstNode>& out_ast);


protected:
    bool _is_main_exe_valid(std::vector<Token>::const_iterator& it, std::vector<Token>::const_iterator& end) const;
    Error _parse_exe(std::vector<Token>::const_iterator& it, std::vector<Token>::const_iterator& end, std::shared_ptr<AstNode>& out_current_ast) const;

    //todo:: implement
    Error _parse_arg(std::vector<Token>::const_iterator& it, std::vector<Token>::const_iterator& end, std::shared_ptr<AstNode>& out_current_ast) const;

    bool _are_enough_tokens_left(
            std::vector<Token>::const_iterator it,
            std::vector<Token>::const_iterator end,
            unsigned int size
    ) const;

};

} // Scripting
} // Koi


#endif //KOI_SCRIPTING_PARSER_HPP
