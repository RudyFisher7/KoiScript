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
    lhs << "executing_key: " << executing_key << ", args: [";

    for (const auto& arg : args) {
        arg->print(lhs);
    }

    lhs << "]";
}




VariableLiteral::VariableLiteral(Variant in_value): value(std::move(in_value)) {

}


void VariableLiteral::print(std::ostream& lhs) const {
    lhs << "value: " << value << " todo::";
}




Value::Value(Variant in_value): value(std::move(in_value)) {

}


void Value::print(std::ostream& lhs) const {
    lhs << "value: " << value << " todo::";
}

} // Scripting
} // Koi