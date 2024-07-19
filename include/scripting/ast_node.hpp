//
// Created by rfish on 7/17/2024.
//

#ifndef KOI_SCRIPTING_AST_NODE_HPP
#define KOI_SCRIPTING_AST_NODE_HPP


#include "scripting/token.hpp"
#include "scripting/type_defs.hpp"
#include "scripting/type.hpp"

#include <string>
#include <memory>
#include <vector>


namespace Koi {
namespace Scripting {

class AstNode {
public:
    std::vector<Token> tokens;
    // scope
    // children
};


class Literal: public AstNode {
public:
    //std::vector<Variant> _args; //fixme:: variant with TypeDecorator
};


class VariableLiteral: public Literal {
public:
    BasicType type = SCRIPTING_BASIC_TYPE_INVALID;
    std::string key;
    std::string value;
};


class FunctionLiteral: public Literal {
public:
    //
};


class Declaration: public AstNode {
public:
    Id id = 0u;
    TypeDecorator type;
};


class Execute: public AstNode {
public:
    TypeDecorator type;
    std::string executing_key;

    std::vector<std::shared_ptr<AstNode>> args;

    Execute();

    explicit Execute(std::string in_executing_key);

    Execute(std::string in_executing_key, TypeDecorator in_type);
};


class Value: public AstNode {
public:
    Id id = 0u;
    //todo:: for type, look up the type of id
};


class Reference: public AstNode {
public:
    // id
    //todo:: for type, look up the type of id
};

} // Scripting
} // Koi

#endif //KOI_SCRIPTING_AST_NODE_HPP
