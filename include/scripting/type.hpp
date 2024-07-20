//
// Created by rfish on 7/17/2024.
//

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
