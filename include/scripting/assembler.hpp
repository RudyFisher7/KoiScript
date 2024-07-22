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


#ifndef KOI_SCRIPTING_ASSEMBLER_HPP
#define KOI_SCRIPTING_ASSEMBLER_HPP


#include "scripting/abstract_syntax_tree/node.hpp"
#include "scripting/runtime/type_defs.hpp"

#include <map>
#include <memory>
#include <vector>


namespace Koi {
namespace Scripting {

class Assembler {
public:
    enum Error : int {
        SCRIPTING_ASSEMBLER_ERROR_MIN = 0,
        SCRIPTING_ASSEMBLER_ERROR_OK = SCRIPTING_ASSEMBLER_ERROR_MIN,
        SCRIPTING_ASSEMBLER_ERROR_SIZE
    };

    Error assemble(
            const std::shared_ptr<Ast::Node> ast_tree,
            std::map<std::string, Runtime::Id>& out_memory_map,
            std::vector<std::shared_ptr<Ast::Node>>& out_memory
    ) const;
};

} // Scripting
} // Koi


#endif //KOI_SCRIPTING_ASSEMBLER_HPP
