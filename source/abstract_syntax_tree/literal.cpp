//
// Created by rfish on 7/20/2024.
//

#include "scripting/abstract_syntax_tree/literal.hpp"

#include <utility>


namespace Koi {
namespace Scripting {
namespace Ast {


VariableLiteral::VariableLiteral(Variant in_value) : value(std::move(in_value)) {

}


void VariableLiteral::print(std::ostream& lhs) const {
    lhs << "{\"_class\": \"VariableLiteral\", \"value\": " << value << "}";
}


Runtime::Error VariableLiteral::evaluate(Variant& out_result) {
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


Runtime::Error FunctionLiteral::evaluate(Variant& out_result) {
    return Runtime::SCRIPTING_RUNTIME_ERROR_OK;
}

} // Ast
} // Scripting
} // Koi