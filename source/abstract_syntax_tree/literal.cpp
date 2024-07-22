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


#include "scripting/abstract_syntax_tree/literal.hpp"

#include <utility>


namespace Koi {
namespace Scripting {
namespace Ast {


VariableLiteral::VariableLiteral(Runtime::Variable in_value) : value(std::move(in_value)) {

}


void VariableLiteral::print(std::ostream& lhs) const {
    lhs << "{\"_class\": \"VariableLiteral\", \"value\": " << value << "}";
}


Runtime::Error VariableLiteral::evaluate(Runtime::Variable& out_result, Runtime::Environment& environment) {
    return Runtime::SCRIPTING_RUNTIME_ERROR_OK;
}


FunctionLiteral::FunctionLiteral(const Type& in_type) : type(in_type), statements({}) {

}


void FunctionLiteral::print(std::ostream& lhs) const {
    lhs << "{\"_class\": \"FunctionLiteral\", \"type\": " << type << ", \"return_statement\": ";
    if (return_statement) {
        lhs << *return_statement;
    } else {
        lhs << "\"<nullptr>\"";
    }

    lhs << ", \"statements\": [";

    auto it = statements.cbegin();
    auto end = statements.cend();

    while (it != end) {
        lhs << **it;
        if ((it + 1u) != end) {
            lhs << ", ";
        }

        ++it;
    }

    lhs << "]}";
}


Runtime::Error FunctionLiteral::evaluate(Runtime::Variable& out_result, Runtime::Environment& environment) {
    Runtime::Error result = Runtime::SCRIPTING_RUNTIME_ERROR_OK;

    unsigned int i = 0u;
    std::vector<Runtime::Variable> argument_values(arguments.size());
    while (result == Runtime::SCRIPTING_RUNTIME_ERROR_OK && i < arguments.size()) {
        result = arguments.at(i)->evaluate(argument_values.at(i), environment);

        ++i;
    }

    i = 0u;
    while (result == Runtime::SCRIPTING_RUNTIME_ERROR_OK && i < statements.size()) {
        Runtime::Variable statement_result;

        result = statements.at(i)->evaluate(statement_result, environment);//fixme::

        ++i;
    }

    if (result == Runtime::SCRIPTING_RUNTIME_ERROR_OK) {
        result = return_statement->evaluate(out_result, environment);
    }

    return result;
}

} // Ast
} // Scripting
} // Koi