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
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ASN_VAR,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ASN_ARR,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ASN_RUN,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_LIB_KOI,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_VAL_VAR,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_VAL_FUN,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_REF_VAR,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_REF_ARR,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_REF_FUN,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_EXE,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_IMP_NATIVE,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_IMP_KOI,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_REM,
        SCRIPTING_RUNTIME_INSTRUCTION_TYPE_SIZE
    };

    Type type;
    BasicType data_type;
    std::vector<BasicType> parameter_types;

    std::string key;
    std::string path;

    int index;
    std::shared_ptr<Variable> value_variable;
    std::shared_ptr<Function> value_function;

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
