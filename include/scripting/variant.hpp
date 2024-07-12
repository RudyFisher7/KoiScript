//
// Created by rfish on 12/28/2023.
//

#ifndef KOI_SCRIPTING_VARIANT_HPP
#define KOI_SCRIPTING_VARIANT_HPP


#include <functional>
#include <ostream>
#include <string>


namespace Koi {
namespace Scripting {

class Variant final {
public:
    enum Type : int {
        SCRIPTING_VARIANT_TYPE_MIN = 0,
        SCRIPTING_VARIANT_TYPE_VOID = SCRIPTING_VARIANT_TYPE_MIN,
        SCRIPTING_VARIANT_TYPE_BOOL,
        SCRIPTING_VARIANT_TYPE_INT,
        SCRIPTING_VARIANT_TYPE_FLOAT,
        SCRIPTING_VARIANT_TYPE_TEXT,
        SCRIPTING_VARIANT_TYPE_REF,
        SCRIPTING_VARIANT_TYPE_SIZE
    };

private:
    Type _current_type = SCRIPTING_VARIANT_TYPE_VOID;
    union {
        bool _value_bool = false;
        int _value_int;
        float _value_float;
        char* _value_text;
        int _value_ref;
    };

public:
    static Variant from_char(char in_value);


    static Variant from_int(int in_value);


    static Variant from_float(float in_value);


    static Variant from_double(double in_value);


    static Variant from_c_string(const char* in_value, size_t size);//todo::

    static Variant from_string(const std::string& in_value);


    static Variant from_variant(const Variant& rhs);


    Variant();


    Variant(char in_value);


    Variant(int in_value);


    Variant(float in_value);


    Variant(double in_value);


    Variant(const char* in_value, size_t size);

    Variant(std::string in_value);


    Variant(const Variant& rhs);


    Variant(Variant&& rhs);


    Variant& operator=(const Variant& rhs);


    Variant& operator=(Variant&& rhs);


    ~Variant();


    bool operator==(const Variant& rhs) const;


    bool operator!=(const Variant& rhs) const;


    int get_type() const;


    operator void() const;//todo::


    operator bool() const;


    operator char() const;


    operator int() const;


    operator float() const;


    operator double() const;


    operator char*() const;


    operator std::string() const;


    bool get_bool() const;

    /**
     * @brief Function that can be used to explicitly get the char
     * representation of the variant when there is ambiguity otherwise
     * such as the cases when interfacing with certain json libraries.
     * @return The char representation of this variant.
     */
    char get_char() const;


    int get_int() const;


    float get_float() const;


    std::string get_string() const;


    void set_value(bool value);


    void set_value(char value);


    void set_value(int value);


    void set_value(float value);


    void set_value(double value);


    void set_value(const char* value, size_t size);
    void set_value(const char* value);//must be null terminated


    void set_value(const std::string& value);


    void morph(Type in_type);


private:
    void _copy(const Variant& rhs);

    bool _set_string_value(const std::string& in_value);


    void _destroy_string_if_string();
};


//todo:: verify this hash is correct
// taken from https://stackoverflow.com/questions/19195183/how-to-properly-hash-the-custom-struct
// which supposedly uses the golden ratio
struct VariantHash {
public:
    size_t operator()(const Variant& in) const noexcept;


private:
    template<typename type>
    void combine_hash(const type& in, size_t& out) const noexcept;
};


std::ostream& operator<<(std::ostream& lhs, const Variant& rhs);


std::string operator+(const Variant& lhs, const std::string& rhs);


std::string operator+(const std::string& lhs, const Variant& rhs);

}
}

#endif //KOI_SCRIPTING_VARIANT_HPP
