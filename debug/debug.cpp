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


//#include "scripting/assembler.hpp"
//#include "scripting/abstract_syntax_tree/node.hpp"
#include "scripting/lexer.hpp"
//#include "scripting/parser.hpp"
#include "scripting/extensions/extensions.hpp"
#include "scripting/runtime/environment.hpp"
#include "scripting/runtime/lib/built_in.hpp"
#include "scripting/runtime/variant/array.hpp"
#include "scripting/runtime/variant/function.hpp"
#include "scripting/runtime/variant/variable.hpp"
#include "scripting/runtime/instruction/instruction.hpp"
#include "scripting/interpreter.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <map>


namespace KoiRuntime = Koi::Scripting::Runtime;


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

    // 1. lex
    Koi::Scripting::Lexer lexer;
    std::vector<Koi::Scripting::Token> tokens;
    lexer.lex(script_buffer, script_size, tokens);

    std::cout << tokens << std::endl;

    //todo:: 2. parse
//    Koi::Scripting::Parser parser;
//    std::shared_ptr<Koi::Scripting::Ast::Node> ast_tree;
//    parser.parse(tokens, ast_tree);
//
//    std::cout << *ast_tree << std::endl;

    //todo:: 3. assemble
    std::shared_ptr<KoiRuntime::Environment> global_environment = std::make_shared<KoiRuntime::Environment>();

    KoiRuntime::BuiltIn built_in_lib;
    built_in_lib.import(global_environment);

    global_environment->declare_var("msg", KoiRuntime::SCRIPTING_RUNTIME_BASIC_TYPE_TEXT);
    global_environment->assign_var("msg", KoiRuntime::Variable("hello world!"));

    KoiRuntime::Ret<KoiRuntime::Variable> ret = std::make_shared<KoiRuntime::Variable>();
    KoiRuntime::Args<KoiRuntime::Variable> args_1 {
        global_environment->get_var_val("msg")
    };

    KoiRuntime::Instruction* first = new KoiRuntime::VariableDeclaration(
        "msg_2",
        nullptr,
        KoiRuntime::SCRIPTING_RUNTIME_BASIC_TYPE_TEXT
    );

    //todo:: 4. run
    Koi::Scripting::Interpreter interpreter;
    KoiRuntime::Error interpreter_error = interpreter.interpret(global_environment, first, ret);

    KoiRuntime::Error fun_res = global_environment->execute_fun("print", ret, args_1);

    KoiRuntime::Args<KoiRuntime::Variable> args_2 {
            std::make_shared<KoiRuntime::Variable>("toasty_array", std::strlen("toasty_array"), KoiRuntime::SCRIPTING_RUNTIME_BASIC_TYPE_KEY),
            std::make_shared<KoiRuntime::Variable>("you got appended me!"),
    };

    KoiRuntime::Error fun_res_2 = global_environment->execute_fun("append", ret, args_2);

    std::cout << *ret << std::endl;

    return 0;
}
