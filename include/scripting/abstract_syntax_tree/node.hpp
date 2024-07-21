//
// Created by rfish on 7/17/2024.
//

#ifndef KOI_SCRIPTING_AST_NODE_HPP
#define KOI_SCRIPTING_AST_NODE_HPP


#include "scripting/runtime/error.hpp"
#include "scripting/token.hpp"
#include "scripting/runtime/type_defs.hpp"
#include "scripting/type.hpp"
#include "scripting/variant.hpp"

#include <ostream>
#include <string>
#include <memory>
#include <vector>


namespace Koi {
namespace Scripting {
namespace Ast {

class Node {
public:
    virtual Runtime::Error evaluate(Variant& out_result) = 0;//fixme:: the result could also be an Ast::Literal
    virtual void print(std::ostream& lhs) const = 0;


    friend std::ostream& operator<<(std::ostream& lhs, const Node& rhs);//fixme:: doesn't work with child runtime types
};


class Statement : public Node {
public:
    //
};


class Declaration : public Statement {
public:
    //
};


class Expression : public Statement {
public:
    //
};

} // Ast
} // Scripting
} // Koi

#endif //KOI_SCRIPTING_AST_NODE_HPP
