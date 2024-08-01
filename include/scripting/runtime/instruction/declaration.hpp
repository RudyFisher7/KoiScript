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


#ifndef KOI_SCRIPTING_RUNTIME_DECLARATION_HPP
#define KOI_SCRIPTING_RUNTIME_DECLARATION_HPP


#include "scripting/runtime/instruction/instruction.hpp"


namespace Koi {
namespace Scripting {
namespace Runtime {

template<Instruction::Type TypeValue>
class DataDeclaration: public Instruction {
protected:
    BasicType _data_type;

public:
    DataDeclaration(
            std::string in_key,
            Instruction* in_next,
            BasicType in_data_type
    ):
            Instruction(TypeValue, std::move(in_key), in_next),
            _data_type(in_data_type) {
    }


    BasicType get_data_type() const {
        return _data_type;
    }
};


typedef DataDeclaration<Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ARR> ArrayDeclaration;
typedef DataDeclaration<Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_VAR> VariableDeclaration;


class FunctionDeclaration: public DataDeclaration<Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_FUN> {
protected:
    std::vector<BasicType> _parameter_types;

public:
    FunctionDeclaration(
            BasicType in_return_type,
            std::string in_key,
            Instruction* in_next,
            std::vector<BasicType> in_parameter_types
    ):
            DataDeclaration(std::move(in_key), in_next, in_return_type),
            _parameter_types(std::move(in_parameter_types)) {
    }


    const std::vector<BasicType>& get_parameter_types() const {
        return _parameter_types;
    }
};

} // Runtime
} // Scripting
} // Koi


#endif //KOI_SCRIPTING_RUNTIME_DECLARATION_HPP
