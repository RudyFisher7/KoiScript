//
// Created by rfish on 7/10/2024.
//


#include "scripting/lexer.hpp"

#include <fstream>
#include <iostream>
#include <string>


int main() {
    std::cout << "KoiScript debug project started" << std::endl;
    std::string script_file_path(R"(C:\dev\koilang\example_scripts\main.koi)");

    std::cout << "Loading " << script_file_path << std::endl;

    std::ifstream script_file(script_file_path);

    std::cout << "done." << std::endl;

    std::string script;
    std::getline(script_file, script);

    std::cout << "Script: " << script << std::endl;

    Koi::Scripting::Lexer lexer;
    lexer.lex(script.c_str(), script.size());

    return 0;
}
