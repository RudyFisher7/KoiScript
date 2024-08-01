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


#ifndef KOI_SCRIPTING_RUNTIME_ASSIGNMENT_HPP
#define KOI_SCRIPTING_RUNTIME_ASSIGNMENT_HPP


#include "scripting/runtime/instruction/instruction.hpp"


namespace Koi {
namespace Scripting {
namespace Runtime {

template<typename T, Instruction::Type TypeValue>
class Assignment: public Instruction {
protected:
    T _data_value;

public:
    Assignment(
            std::string in_key,
            Instruction* in_next,
            T in_data_value
    ):
            Instruction(TypeValue, in_key, in_next),
            _data_value(std::move(in_data_value)) {
    }

    const T& get_value() const {
        return _data_value;
    }
};


typedef Assignment<Variable, Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ASN_VAR> VariableAssignment;
typedef Assignment<Function, Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ASN_FUN> FunctionAssignment;


class ArrayElementAssignment: public Assignment<Variable, Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ASN_ARR> {
protected:
    int _index;

public:
    ArrayElementAssignment(
            std::string in_key,
            Instruction* in_next,
            Variable in_data_value,
            int in_index
    ):
            Assignment(std::move(in_key), in_next, std::move(in_data_value)),
            _index(in_index) {
    }

    int get_index() const {
        return _index;
    }
};

}
}
}


#endif //KOI_SCRIPTING_RUNTIME_ASSIGNMENT_HPP
