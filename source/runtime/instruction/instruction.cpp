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


#include "scripting/runtime/instruction/instruction.hpp"


namespace Koi {
namespace Scripting {
namespace Runtime {

Instruction::Instruction(
        Type in_type,
        std::string in_key,
        Instruction* in_next
): _type(in_type), _key(std::move(in_key)), _next(in_next) {

}


Instruction::Type Instruction::get_type() const {
    return _type;
}


std::string Instruction::get_key() const {
    return _key;
}


Instruction* Instruction::get_next() {
    return _next;
}


void Instruction::set_next(Instruction* value) {
    delete _next;
    _next = value;
}


Instruction::~Instruction() {
        delete _next;
}

} // Runtime
} // Scripting
} // Koi