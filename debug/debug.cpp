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
#include "scripting/runtime/variant/array.hpp"
#include "scripting/runtime/variant/variable.hpp"

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

    // var<toasty>:text;
    global_environment->declare_var("toasty", KoiRuntime::SCRIPTING_RUNTIME_BASIC_TYPE_TEXT);

    // var<toasty>:float[];
    global_environment->declare_arr("toasty_array", KoiRuntime::SCRIPTING_RUNTIME_BASIC_TYPE_FLOAT);

    // ref<toasty>();
    std::shared_ptr<KoiRuntime::Variable> toasty = global_environment->get_var_ref("toasty");

    // exe<assign>(ref<toasty>(), 'hello world!');
    toasty->set_value("hello world!");

    // ref<toasty_array>();
    std::shared_ptr<KoiRuntime::Array> toasty_array = global_environment->get_arr_ref("toasty_array");

    // exe<append>(ref<toasty_array>(), 'hello world!');
    toasty_array->emplace_back("hello world!");

    // exe<append>(ref<toasty_array>(), 'howdy USA!');
    toasty_array->emplace_back("howdy USA!");

    // exe<append>(ref<toasty_array>(), 'konnichiwa nihon!');
    toasty_array->emplace_back("konnichiwa nihon!");

    {
        std::shared_ptr<KoiRuntime::Environment> child_environment = KoiRuntime::Environment::make_child_environment(
                global_environment
        );

        // ref<toasty>();
        std::shared_ptr<KoiRuntime::Variable> toasty_from_child = child_environment->get_var_ref("toasty");

        // exe<assign>(ref<toasty>(), 'sayonara');
        toasty->set_value("sayonara");
    }


    //todo:: 4. run

    return 0;
}
