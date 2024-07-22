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
