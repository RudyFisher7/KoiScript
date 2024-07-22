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


#ifndef KOI_SCRIPTING_AST_META_HPP
#define KOI_SCRIPTING_AST_META_HPP


#include "scripting/abstract_syntax_tree/node.hpp"
#include "scripting/abstract_syntax_tree/literal.hpp"
#include "scripting/runtime/error.hpp"
#include "scripting/runtime/type_defs.hpp"

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


    Runtime::Error evaluate(Runtime::Variable& out_result, Runtime::Environment& environment) override;


    void print(std::ostream& lhs) const override;
};


class ValueMeta : public Expression {
public:
    //fixme:: this needs an id
    Runtime::Id value;


    explicit ValueMeta(Runtime::Id in_value);

    Runtime::Error evaluate(Runtime::Variable& out_result, Runtime::Environment& environment) override;


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
