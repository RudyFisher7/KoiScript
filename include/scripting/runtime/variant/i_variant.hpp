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


#ifndef KOI_SCRIPTING_RUNTIME_VARIANT_HPP
#define KOI_SCRIPTING_RUNTIME_VARIANT_HPP


#include "scripting/runtime/basic_type.hpp"

#include <string>
#include <memory>


namespace Koi {
namespace Scripting {
namespace Runtime {

class IVariant {
public:
    enum Type: int {
        SCRIPTING_RUNTIME_VARIANT_TYPE_INVALID = -1,
        SCRIPTING_RUNTIME_VARIANT_TYPE_MIN = 0,
        SCRIPTING_RUNTIME_VARIANT_TYPE_VAR = SCRIPTING_RUNTIME_VARIANT_TYPE_MIN,
        SCRIPTING_RUNTIME_VARIANT_TYPE_REF,
        SCRIPTING_RUNTIME_VARIANT_TYPE_ARR,
        SCRIPTING_RUNTIME_VARIANT_TYPE_FUN,
        SCRIPTING_RUNTIME_VARIANT_TYPE_SIZE
    };


protected:
    Type _variant_type = SCRIPTING_RUNTIME_VARIANT_TYPE_INVALID;
    BasicType _type = SCRIPTING_RUNTIME_BASIC_TYPE_INVALID;


public:
    IVariant() = default;
    explicit IVariant(Type in_type);

    IVariant(const IVariant& rhs) = default;
    IVariant(IVariant&& rhs) = default;

    virtual ~IVariant() = default;

    IVariant& operator=(const IVariant& rhs) = default;
    IVariant& operator=(IVariant&& rhs) = default;

    bool operator==(const IVariant& rhs) const;
    bool operator!=(const IVariant& rhs) const;


    virtual explicit operator bool() const;
    virtual explicit operator char() const;
    virtual explicit operator int() const;
    virtual explicit operator float() const;
    virtual explicit operator const char*() const;
    virtual explicit operator std::string() const;

    Type get_variant_type() const;

    virtual BasicType get_type() const;

    virtual int get_size() const = 0;
    virtual bool get_bool() const = 0;
    virtual char get_char() const = 0;
    virtual int get_int() const = 0;
    virtual float get_float() const = 0;
    virtual const char* get_c_string() const = 0;
    virtual std::string get_string() const = 0;
    virtual std::shared_ptr<IVariant> clone() const = 0;

protected:
    virtual bool _equals(const IVariant& rhs) const = 0;
};

} // Runtime
} // Scripting
} // Koi

#endif //KOI_SCRIPTING_RUNTIME_VARIANT_HPP
