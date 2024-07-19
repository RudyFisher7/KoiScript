//
// Created by rfish on 7/10/2024.
//


#include "scripting/ast_node.hpp"
#include "scripting/lexer.hpp"
#include "scripting/parser.hpp"
#include "scripting/extensions/extensions.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>


int main() {
    std::cout << "KoiScript debug project started" << std::endl;
    std::string script_file_path(R"(C:\dev\koilang\example_scripts\hello_world.koi)");

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
    std::shared_ptr<Koi::Scripting::AstNode> ast_tree;
    parser.parse(tokens, ast_tree);

    ast_tree->print();

    return 0;
}
