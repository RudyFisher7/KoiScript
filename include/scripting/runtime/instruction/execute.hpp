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


#ifndef KOI_SCRIPTING_RUNTIME_EXECUTE_HPP
#define KOI_SCRIPTING_RUNTIME_EXECUTE_HPP


#include "scripting/runtime/instruction/instruction.hpp"

#include <vector>


namespace Koi {
namespace Scripting {
namespace Runtime {

template<Instruction::Type TypeValue>
class Execute: public Instruction {
protected:
    std::vector<Instruction*> _argument_instructions;

public:
    Execute(
            std::string in_key,
            Instruction* in_next,
            std::vector<Instruction*> in_argument_instructions
    ):
            Instruction(TypeValue, in_key, in_next),
            _argument_instructions(std::move(in_argument_instructions)) {
    }

    const std::vector<Instruction*>& get_argument_instructions() const {
        return _argument_instructions;
    }
};


typedef Execute<Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_EXE_NATIVE> ExecuteNative;

}
}
}


#endif //KOI_SCRIPTING_RUNTIME_EXECUTE_HPP
