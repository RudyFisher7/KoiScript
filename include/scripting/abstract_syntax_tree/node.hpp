//
// Created by rfish on 7/17/2024.
//

#ifndef KOI_SCRIPTING_AST_NODE_HPP
#define KOI_SCRIPTING_AST_NODE_HPP


#include "scripting/token.hpp"
#include "scripting/type_defs.hpp"
#include "scripting/type.hpp"
#include "scripting/variant.hpp"

#include <ostream>
#include <string>
#include <memory>
#include <vector>


namespace Koi {
namespace Scripting {
namespace Ast {

class AstNode {
public:
    std::vector<Token> tokens;


    // scope
    // children
    friend std::ostream& operator<<(std::ostream& lhs, const AstNode& rhs);


    virtual void print(std::ostream& lhs) const {
    }


};


class Statement : public AstNode {
public:
    //
};


class Declaration : public Statement {
public:
    //
};


class VariableMeta : public Declaration {
public:
    std::string key;
    VariableLiteral value;
};


class FunctionMeta : public Declaration {
public:
    std::string key;
    FunctionLiteral value;
};


class Expression : public Statement {
public:
    //
};


class ExecuteMeta : public Expression {
public:
    std::string executing_key;

    std::vector<std::shared_ptr<AstNode>> args;


    ExecuteMeta();


    explicit ExecuteMeta(std::string in_executing_key);


    ExecuteMeta(std::string in_executing_key, TypeDecorator in_type);


    void print(std::ostream& lhs) const override;
};


class ValueMeta : public Expression {
public:
    Variant value;


    explicit ValueMeta(Variant in_value);


    void print(std::ostream& lhs) const override;
};


class ReferenceMeta : public Expression {
public:
    // id
    //todo:: for type, look up the type of id
};

} // Ast
} // Scripting
} // Koi

#endif //KOI_SCRIPTING_AST_NODE_HPP
