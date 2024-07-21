//
// Created by rfish on 7/20/2024.
//

#ifndef KOI_SCRIPTING_AST_META_HPP
#define KOI_SCRIPTING_AST_META_HPP


#include "scripting/abstract_syntax_tree/node.hpp"
#include "scripting/abstract_syntax_tree/literal.hpp"
#include "scripting/runtime/error.hpp"

#include <string>


namespace Koi {
namespace Scripting {
namespace Ast {

class VariableMeta : public Declaration {
public:
    std::string key;
    std::shared_ptr<VariableLiteral> value;
};


class FunctionMeta : public Declaration {
public:
    std::string key;
    std::shared_ptr<FunctionLiteral> value;
};


class ExecuteMeta : public Expression {
public:
    std::string executing_key;

    std::vector<std::shared_ptr<Expression>> args;


    ExecuteMeta();


    explicit ExecuteMeta(std::string in_executing_key);


    ExecuteMeta(std::string in_executing_key, TypeDecorator in_type);


    Runtime::Error evaluate(Variant& out_result) override;


    void print(std::ostream& lhs) const override;
};


class ValueMeta : public Expression {
public:
    Variant value;


    explicit ValueMeta(Variant in_value);

    Runtime::Error evaluate(Variant& out_result) override;


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

#endif //KOI_SCRIPTING_AST_META_HPP
