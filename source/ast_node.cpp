//
// Created by rfish on 7/17/2024.
//


#include "scripting/ast_node.hpp"

#include <utility>


namespace Koi {
namespace Scripting {


std::ostream& operator<<(std::ostream& lhs, const AstNode& rhs) {
    rhs.print(lhs);

    return lhs;
}




Execute::Execute(): executing_key(), args({}) {

}


Execute::Execute(std::string in_executing_key):
        executing_key(std::move(in_executing_key)),
        args({}) {

}


Execute::Execute(std::string in_executing_key, TypeDecorator in_type):
        executing_key(std::move(in_executing_key)),
        args({}) {

}


void Execute::print(std::ostream& lhs) const {
    lhs << "{\"_class:\": \"Execute\", \"executing_key\": \"" << executing_key << "\", \"args\": [";

    auto it = args.cbegin();
    auto end = args.cend();

    while (it != end) {
        (*it)->print(lhs);
        if ((it + 1u) != end) {
            lhs << ", ";
        }

        ++it;
    }

    lhs << "]}";
}




VariableLiteral::VariableLiteral(Variant in_value): value(std::move(in_value)) {

}


void VariableLiteral::print(std::ostream& lhs) const {
    lhs << "{\"_class:\": \"VariableLiteral\", \"value\": " << value << "}";
}



FunctionLiteral::FunctionLiteral(const Type& in_type): type(in_type), statements({}) {

}


void FunctionLiteral::print(std::ostream& lhs) const {
    lhs << "{\"_class:\": \"FunctionLiteral\", \"type\": " << type << ", \"return_statement\": ";
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



Value::Value(Variant in_value): value(std::move(in_value)) {

}


void Value::print(std::ostream& lhs) const {
    lhs << "{\"_class:\": \"Value\", \"value\": " << value << " todo::}";
}

} // Scripting
} // Koi