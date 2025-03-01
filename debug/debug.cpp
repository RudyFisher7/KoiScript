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
#include "scripting/token.hpp"
//#include "scripting/parser.hpp"
//#include "scripting/extensions/extensions.hpp"
//#include "scripting/runtime/environment.hpp"
//#include "scripting/runtime/lib/built_in.hpp"
//#include "scripting/runtime/variant/array.hpp"
//#include "scripting/runtime/variant/function.hpp"
//#include "scripting/runtime/variant/variable.hpp"
//#include "scripting/runtime/instruction/instruction.hpp"
//#include "scripting/interpreter.hpp"

//#include <cstring>
//#include <fstream>
#include <iostream>
#include <vector>
//#include <string>
//#include <memory>
//#include <map>


int main() {
    std::cout << "KoiScript debug project started" << std::endl;

    // 1. lex
    std::vector<Koi::Scripting::Token> tokens;
    Koi::Scripting::Lexer lexer;
    lexer.lex(R"(C:\dev\koi_script\example_scripts\brainstorm.koi)", tokens);

    for (auto& token: tokens) {
        std::cout << "Token: " << lexer.get_token_type_name(token.type) << ", " << token.text << ", " << token.file_path << ":" << token.line_index << std::endl;
    }

    //todo:: 2. parse

    //todo:: 3. assemble

    //todo:: 4. run

    return 0;
}
