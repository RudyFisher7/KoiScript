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


#include "scripting/assembler.hpp"
#include "scripting/abstract_syntax_tree/node.hpp"
#include "scripting/koi_script.hpp"
#include "scripting/lexer.hpp"
//#include "scripting/parser.hpp"
#include "scripting/extensions/extensions.hpp"
#include "scripting/runtime/environment.hpp"
#include "scripting/runtime/data/function.hpp"
#include "scripting/runtime/meta/i_meta.hpp"
#include "scripting/runtime/meta/exe.hpp"
#include "scripting/runtime/meta/main.hpp"
#include "scripting/runtime/meta/print.hpp"
#include "scripting/runtime/data/variable.hpp"
#include "scripting/runtime/data/variant.hpp"

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

    // 2. parse
//    Koi::Scripting::Parser parser;
//    std::shared_ptr<Koi::Scripting::Ast::Node> ast_tree;
//    parser.parse(tokens, ast_tree);
//
//    std::cout << *ast_tree << std::endl;

    //todo:: 3. assemble
    Koi::Scripting::Runtime::Environment global_environment;
    Koi::Scripting::Assembler assembler;

    assembler.assemble(global_environment);


    std::shared_ptr<KoiRuntime::Environment> main_environment = std::make_shared<KoiRuntime::Environment>();
    std::shared_ptr<const KoiRuntime::Environment> parent = std::make_shared<const KoiRuntime::Environment>(global_environment);
    main_environment->set_parent_environment(parent);

    std::shared_ptr<KoiRuntime::IMeta> main_meta = std::make_shared<KoiRuntime::Main>();
    std::shared_ptr<KoiRuntime::IMeta> print_meta = std::make_shared<KoiRuntime::Print>();

    global_environment.register_declaration(main_meta->get_key());
    global_environment.register_assignment(main_meta->get_key(), main_meta);
    global_environment.register_declaration(print_meta->get_key());
    global_environment.register_assignment(print_meta->get_key(), print_meta);



    //todo:: 4. run
    Koi::Scripting::Runtime::Variant runtime_result;

    KoiRuntime::IMeta::Args main_args(2u);
    main_args.at(0u) = std::make_shared<const KoiRuntime::LitVal>(KoiRuntime::Variant(KoiRuntime::Variable("hello world!")));

    KoiRuntime::IExe::Body body;
    body.push_back(print_meta);
    body.push_back(std::make_shared<const KoiRuntime::LitVal>(KoiRuntime::Variant(KoiRuntime::Variable(33))));
    main_args.at(1u) = std::make_shared<const KoiRuntime::Exe>("root-fixme::", body);

    main_meta->run(main_args, runtime_result);

//    KoiRuntime::IMeta::Args print_args;
//    KoiRuntime::Variant str(KoiRuntime::Variable("hello world!"));
//    std::shared_ptr<const KoiRuntime::IMeta> arg = std::make_shared<const KoiRuntime::LitVal>(str);
//    print_args.push_back(arg);
//    print_meta->run(print_args, runtime_result);

    std::cout << "Runtime result: " << runtime_result.get_variable() << std::endl;

    return 0;
}
