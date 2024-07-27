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


#ifndef KOI_SCRIPTING_EXE_HPP
#define KOI_SCRIPTING_EXE_HPP


#include "i_meta.hpp"

#include "scripting/runtime/error.hpp"
#include "scripting/runtime/environment.hpp"
#include "scripting/runtime/data/function.hpp"
#include "scripting/runtime/data/variant.hpp"

#include <string>
#include <memory>
#include <vector>


namespace Koi {
namespace Scripting {
namespace Runtime {

class Exe: public IExe {
protected:
    std::string _key;
    IExe::Body _body_meta_instructions;//fixme:: this probably needs to change for using current values in the runtime environments


public:
    Exe();

    Exe(std::string in_key, IExe::Body in_body_meta_instructions);

    Exe(const Exe& rhs) = default;
    Exe(Exe&& rhs) = default;

    virtual ~Exe();

    Exe& operator=(const Exe& rhs) = default;
    Exe& operator=(Exe&& rhs) = default;

    std::string get_key() const override;
    Error run(IMeta::Args arguments, IMeta& out_result) const override;
};

} // Runtime
} // Scripting
} // Koi


#endif //KOI_SCRIPTING_EXE_HPP
