//
// Created by rfish on 7/17/2024.
//

#ifndef KOI_SCRIPTING_AST_NODE_HPP
#define KOI_SCRIPTING_AST_NODE_HPP


#include "scripting/token.hpp"
#include "scripting/type_defs.hpp"
#include "scripting/type.hpp"
#include "scripting/variant.hpp"

#include <iostream>
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
    friend std::ostream& operator<<(std::ostream& lhs, const AstNode& rhs);


    virtual void print(std::ostream& lhs) const { }


};


class Literal: public AstNode {
public:
    //std::vector<Variant> _args; //fixme:: variant with TypeDecorator
};


class VariableLiteral: public Literal {
public:
    Variant value;

    explicit VariableLiteral(Variant in_value);

    void print(std::ostream& lhs) const override;
};


class FunctionLiteral: public Literal {
public:
    Type type;
    std::shared_ptr<AstNode> return_statement;
    std::vector<std::shared_ptr<AstNode>> statements;

    explicit FunctionLiteral(const Type& in_type);//fixme:: rule of 5 stuff
    void print(std::ostream& lhs) const override;
};


class Declaration: public AstNode {
public:
    Id id = 0u;
    TypeDecorator type;
};


class Execute: public AstNode {
public:
    std::string executing_key;

    std::vector<std::shared_ptr<AstNode>> args;

    Execute();

    explicit Execute(std::string in_executing_key);

    Execute(std::string in_executing_key, TypeDecorator in_type);
    void print(std::ostream& lhs) const override;
};


class Value: public AstNode {
public:
    Variant value;

    explicit Value(Variant in_value);

    void print(std::ostream& lhs) const override;
};


class Reference: public AstNode {
public:
    // id
    //todo:: for type, look up the type of id
};

} // Scripting
} // Koi

#endif //KOI_SCRIPTING_AST_NODE_HPP
