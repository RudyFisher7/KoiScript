//
// Created by rfish on 7/10/2024.
//


#include "scripting/lexer.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>


int main() {
    std::cout << "KoiScript debug project started" << std::endl;
    std::string script_file_path(R"(C:\dev\koilang\example_scripts\master.koi)");

    std::cout << "Loading " << script_file_path << std::endl;

    std::ifstream script_file(script_file_path);

    std::cout << "done." << std::endl;

    std::string script;
    script_file.seekg(0, std::ifstream::end);

    unsigned long script_size = script_file.tellg();
    char* const script_buffer = new char[script_size + 1u];
    std::memset(script_buffer, 0, script_size + 1u);

    script_file.seekg(0, std::ifstream::beg);
    script_file.read(script_buffer, script_size);

    script_buffer[script_size] = '\0';

    std::cout << "Script: " << script_buffer << std::endl;

    Koi::Scripting::Lexer lexer;
    std::vector<Koi::Scripting::Token>& tokens = lexer.lex(script_buffer, script_size);

    for(const auto& token : tokens) {
        std::cout << token << "\n";
    }

    std::cout << std::endl;

    std::string prefix = "";
    for(const auto& token : tokens) {
        if (token.value == "}") {
            prefix.erase(0, 1);
        } else {

        }

        std::cout << token.value;
        if (token.value == ";") {
            std::cout << '\n';
        } else if (token.value == "{") {
            std::cout << "\n\t";
            prefix += "\t";
        }

        if (token.type == Koi::Scripting::Token::SCRIPTING_TOKEN_TYPE_INVALID) {
            std::cout << "!!!!!!!!INVALID!!!!!!!!!" << std::endl;
        }
    }

    std::cout << std::endl;

    return 0;
}
