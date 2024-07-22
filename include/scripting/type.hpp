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


#ifndef KOI_SCRIPTING_TYPE_HPP
#define KOI_SCRIPTING_TYPE_HPP


#include <iostream>
#include <vector>


namespace Koi {
namespace Scripting {

enum BasicType: int {
    SCRIPTING_BASIC_TYPE_INVALID = -1,
    SCRIPTING_BASIC_TYPE_MIN = 0,
    SCRIPTING_BASIC_TYPE_VOID = SCRIPTING_BASIC_TYPE_MIN,
    SCRIPTING_BASIC_TYPE_BOOL,
    SCRIPTING_BASIC_TYPE_INT,
    SCRIPTING_BASIC_TYPE_FLOAT,
    SCRIPTING_BASIC_TYPE_TEXT,
    SCRIPTING_BASIC_TYPE_REF,
    SCRIPTING_BASIC_TYPE_SIZE,
};


class Type {
public:
    BasicType return_type = SCRIPTING_BASIC_TYPE_INVALID;
    unsigned int array_dimensions = 0u;
    std::vector<BasicType> parameter_types;


    Type();

    explicit Type(BasicType in_return_type);

    Type(
            BasicType in_return_type,
            unsigned int in_array_dimensions,
            std::vector<BasicType>&& in_parameter_types
    );

    virtual ~Type();//fixme:: implement this and other rule of 5 stuff

    friend std::ostream& operator<<(std::ostream& lhs, const Type& rhs);
};


//fixme:: i don't think this is quite right
/**
 * @brief A type using the decorator pattern to allow for infinitely-layered
 * return types.
 */
class TypeDecorator: public Type {
protected:
    TypeDecorator* _return_type_decorator = nullptr;


public:

    //todo:: constructor and things.
    TypeDecorator* get_next_return_type() const;
};

}
}


#endif //KOI_SCRIPTING_TYPE_HPP
