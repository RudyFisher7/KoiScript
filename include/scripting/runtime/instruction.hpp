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


#ifndef KOI_SCRIPTING_RUNTIME_INSTRUCTION_HPP
#define KOI_SCRIPTING_RUNTIME_INSTRUCTION_HPP


#include "scripting/runtime/basic_type.hpp"
#include "scripting/runtime/variant/array.hpp"
#include "scripting/runtime/variant/function.hpp"
#include "scripting/runtime/variant/variable.hpp"

#include <memory>
#include <string>
#include <vector>


namespace Koi {
namespace Scripting {
namespace Runtime {

class Instruction {
public:
    enum Type: int {
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_MIN = 0,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_VAR = SCRIPTING_RUNTIME_INSTRUCTION_TYPE_MIN,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ARR,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_FUN,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_LIB,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_VAL,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_REF,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ASN,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_EXE,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_IMP,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_SIZE
    };


    Type type;
    BasicType data_type;
    std::vector<BasicType> parameter_types;

    std::string key;
    std::string path;

    std::shared_ptr<Variable> value_variable;
    std::shared_ptr<Function> value_function;
    std::shared_ptr<Array> value_array;

    std::shared_ptr<Instruction> next;


    Instruction(
            Type type,
            BasicType data_type,
            std::string  key,
            std::shared_ptr<Instruction> next
    );

};


template<typename T>
class InstructionT: public Instruction {
public:

};

} // Runtime
} // Scripting
} // Koi

#endif //KOI_SCRIPTING_RUNTIME_INSTRUCTION_HPP
