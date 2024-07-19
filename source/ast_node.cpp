//
// Created by rfish on 7/17/2024.
//


#include "scripting/ast_node.hpp"

#include <utility>


namespace Koi {
namespace Scripting {

Execute::Execute(): type(), executing_key(), args({}) {

}


Execute::Execute(std::string in_executing_key):
        type(),
        executing_key(std::move(in_executing_key)),
        args({}) {

}


Execute::Execute(std::string in_executing_key, TypeDecorator in_type):
        type(std::move(in_type)),
        executing_key(std::move(in_executing_key)),
        args({}) {

}


void Execute::print() const {
    std::cout << "executing_key: " << executing_key << ", args: todo::" << std::endl;
}

} // Scripting
} // Koi