//
// Created by rfish on 7/10/2024.
//


#include "scripting/assembler.hpp"
#include "scripting/abstract_syntax_tree/node.hpp"
#include "scripting/lexer.hpp"
#include "scripting/parser.hpp"
#include "scripting/runtime/type_defs.hpp"
#include "scripting/extensions/extensions.hpp"
#include "scripting/variant.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <map>


int main() {
    std::cout << "KoiScript debug project started" << std::endl;
    std::string script_file_path(R"(..\example_scripts\hello_world.koi)");

    std::cout << "Loading " << script_file_path << std::endl;

    std::ifstream script_file(script_file_path);

    std::cout << "done.\n" << std::endl;

    std::string script;
    script_file.seekg(0, std::ifstream::end);

    unsigned long script_size = script_file.tellg();
    char* const script_buffer = new char[script_size + 1u];
    std::memset(script_buffer, 0, script_size + 1u);

    script_file.seekg(0, std::ifstream::beg);
    script_file.read(script_buffer, script_size);

    script_buffer[script_size] = '\0';

    std::cout << "Script:\n" << script_buffer << '\n' << std::endl;

    Koi::Scripting::Lexer lexer;
    std::vector<Koi::Scripting::Token> tokens;
    lexer.lex(script_buffer, script_size, tokens);

    std::cout << tokens << std::endl;

    Koi::Scripting::Parser parser;
    std::shared_ptr<Koi::Scripting::Ast::Node> ast_tree;
    parser.parse(tokens, ast_tree);

    std::cout << *ast_tree << std::endl;

    std::map<std::string, Koi::Scripting::Runtime::Id> memory_map {};
    std::vector<std::shared_ptr<Koi::Scripting::Ast::Node>> memory {};

    Koi::Scripting::Variant runtime_result;
    ast_tree->evaluate(runtime_result);

    std::cout << "Runtime result: " << runtime_result << std::endl;

    Koi::Scripting::Assembler assembler;

    assembler.assemble(ast_tree, memory_map, memory);

    return 0;
}
