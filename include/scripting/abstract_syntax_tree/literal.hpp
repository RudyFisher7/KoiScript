//
// Created by rfish on 7/20/2024.
//

#ifndef KOI_SCRIPTING_AST_LITERAL_HPP
#define KOI_SCRIPTING_AST_LITERAL_HPP


#include "scripting/abstract_syntax_tree/node.hpp"

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

class Literal : public Expression {

};


class VariableLiteral : public Literal {
public:
    Variant value;


    explicit VariableLiteral(Variant in_value);

    Runtime::Error evaluate(Variant& out_result) override;


    void print(std::ostream& lhs) const override;
};


class FunctionLiteral : public Literal {
public:
    Type type;
    std::shared_ptr<Statement> return_statement;
    std::vector<std::shared_ptr<Statement>> statements;


    explicit FunctionLiteral(const Type& in_type);//fixme:: rule of 5 stuff
    Runtime::Error evaluate(Variant& out_result) override;
    void print(std::ostream& lhs) const override;
};

} // Ast
} // Scripting
} // Koi


#endif //KOI_SCRIPTING_AST_LITERAL_HPP
