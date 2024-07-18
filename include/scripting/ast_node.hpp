//
// Created by rfish on 7/17/2024.
//

#ifndef KOI_SCRIPTING_AST_NODE_HPP
#define KOI_SCRIPTING_AST_NODE_HPP


#include "scripting/token.hpp"
#include "scripting/type_defs.hpp"
#include "scripting/type.hpp"

#include <string>
#include <vector>


namespace Koi {
namespace Scripting {

class AstNode {
public:
    Token token;
    // scope
    // children
};


class Literal: public AstNode {
public:
    TypeDecorator type;
    //std::vector<Variant> _args; //fixme:: variant with TypeDecorator
};


class Declaration: public AstNode {
public:
    Id id = 0u;
    TypeDecorator type;
};


class Execute: public AstNode {
public:
    TypeDecorator type;
    Id id = 0u;

    Execute();

    Execute(Id in_id);

    Execute(Id in_id, TypeDecorator in_type);
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
