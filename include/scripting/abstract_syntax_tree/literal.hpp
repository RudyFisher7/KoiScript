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
