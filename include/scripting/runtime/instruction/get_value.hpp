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


/**
 * @brief BasicType-safe value getter instructions.
 * @remarks Currently not used.
 */


#ifndef KOI_SCRIPTING_RUNTIME_GET_VALUE_HPP
#define KOI_SCRIPTING_RUNTIME_GET_VALUE_HPP


#include "scripting/runtime/instruction/instruction.hpp"

#include "scripting/runtime/basic_type.hpp"

#include <utility>
#include <string>
#include <vector>


namespace Koi {
namespace Scripting {
namespace Runtime {

class GetVariableValue: public Instruction {
protected:
    BasicType _data_type;

public:
    GetVariableValue(
            std::string in_key,
            Instruction* in_next,
            BasicType in_data_type
    ):
            Instruction(Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_VAL_VAR, std::move(in_key), in_next),
            _data_type(in_data_type) {
    }

    BasicType get_data_type() const {
        return _data_type;
    }
};


class GetArrayElementValue: public Instruction {
protected:
    BasicType _data_type;
    int _index;

public:
    GetArrayElementValue(
            std::string in_key,
            Instruction* in_next,
            BasicType in_data_type,
            int in_index
    ):
            Instruction(Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_VAL_ARR_VAR, std::move(in_key), in_next),
            _data_type(in_data_type),
            _index(in_index) {
    }

    BasicType get_data_type() const {
        return _data_type;
    }

    int get_index() const {
        return _index;
    }
};


class GetFunctionValue: public Instruction {
protected:
    BasicType _return_type;
    std::vector<BasicType> _parameter_types;

public:
    GetFunctionValue(
            std::string in_key,
            Instruction* in_next,
            BasicType in_return_type,
            const std::vector<BasicType>& in_parameter_types
    ):
            Instruction(Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_VAL_FUN, std::move(in_key), in_next),
            _return_type(in_return_type),
            _parameter_types(in_parameter_types) {
    }

    BasicType get_return_type() const {
        return _return_type;
    }

    unsigned int get_number_of_arguments() const {
        return _parameter_types.size();
    }

    BasicType get_argument_type_at(unsigned int i) {
        return _parameter_types.at(i);
    }
};

}
}
}


#endif //KOI_SCRIPTING_RUNTIME_GET_VALUE_HPP
