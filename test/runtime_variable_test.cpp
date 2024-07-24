/*
 * MIT License
 *
 * Copyright (c) 2024 kiyasui-hito
 *
 * Permission is hereby granted, free of charge, to any person obtaining expected copy
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


#include "scripting/runtime/variable.hpp"
#include "scripting/type.hpp"

#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cstring>
#include <string>
#include <limits>


namespace KoiScript = Koi::Scripting;


TEST_CASE("Variable get value - type void", "[VARIABLE][VOID]") {
    KoiScript::Runtime::Variable variable;

    CHECK(variable.get_type() == KoiScript::SCRIPTING_BASIC_TYPE_VOID);
    CHECK(variable.get_size() == 0u);

    SECTION("Get bool") {
        CHECK_FALSE(variable.get_bool());
    }

    SECTION("Get char") {
        CHECK(variable.get_char() == '\0');
    }

    SECTION("Get int") {
        CHECK(variable.get_int() == 0);
    }

    SECTION("Get float") {
        CHECK(variable.get_float() == 0.0f);
    }

    SECTION("Get text") {
        CHECK(variable.get_string() == KoiScript::Runtime::Variable::VOID_STRING);
    }

    SECTION("Get all") {
        CHECK_FALSE(variable.get_bool());
        CHECK(variable.get_char() == '\0');
        CHECK(variable.get_int() == 0);
        CHECK(variable.get_float() == 0.0f);
        CHECK(variable.get_string() == KoiScript::Runtime::Variable::VOID_STRING);
    }
}


TEST_CASE("Variable set value - type void", "[VARIABLE][VOID]") {
    KoiScript::Runtime::Variable variable;

    CHECK(variable.get_type() == KoiScript::SCRIPTING_BASIC_TYPE_VOID);
    CHECK(variable.get_size() == 0u);

    SECTION("bool") {
        variable.set_value(true);
        CHECK(variable.get_bool());
        CHECK(variable.get_type() == KoiScript::SCRIPTING_BASIC_TYPE_BOOL);
        CHECK(variable.get_size() == sizeof(bool));
    }

    SECTION("char") {
        char expected = 'a';
        variable.set_value(expected);
        CHECK(variable.get_char() == expected);
        CHECK(variable.get_type() == KoiScript::SCRIPTING_BASIC_TYPE_TEXT);
        CHECK(variable.get_size() == 1u);
    }

    SECTION("int") {
        int expected = 8;
        variable.set_value(expected);
        CHECK(variable.get_int() == expected);
        CHECK(variable.get_type() == KoiScript::SCRIPTING_BASIC_TYPE_INT);
        CHECK(variable.get_size() == sizeof(int));
    }

    SECTION("float") {
        float expected = 8.14f;
        variable.set_value(expected);
        CHECK(variable.get_float() == expected);
        CHECK(variable.get_type() == KoiScript::SCRIPTING_BASIC_TYPE_FLOAT);
        CHECK(variable.get_size() == sizeof(float));
    }

    SECTION("text") {
        const char* expected = "toasty text";
        variable.set_value(expected);
        CHECK(variable.get_string() == expected);
        CHECK(variable.get_type() == KoiScript::SCRIPTING_BASIC_TYPE_TEXT);
        CHECK(variable.get_size() == std::strlen(expected));
    }
}


TEST_CASE("Variable get value - type text", "[VARIABLE][TEXT]") {
    const char* toasty_text = "toasty text";
    KoiScript::Runtime::Variable variable(toasty_text);

    CHECK(variable.get_type() == KoiScript::SCRIPTING_BASIC_TYPE_TEXT);
    CHECK(variable.get_size() == std::strlen(toasty_text));

    SECTION("Get bool") {
        CHECK(variable.get_bool());
    }

    SECTION("Get char") {
        CHECK(variable.get_char() == toasty_text[0u]);
    }

    SECTION("Get int") {
        CHECK(variable.get_int() == static_cast<int>(toasty_text[0u]));
    }

    SECTION("Get float") {
        CHECK(variable.get_float() == static_cast<float>(toasty_text[0u]));
    }

    SECTION("Get text") {
        CHECK(variable.get_string() == toasty_text);

        // these must be pointing to different memory addresses (deep copy
        // in constructor).
        CHECK_FALSE(variable.get_c_string() == toasty_text);//fixme:: this isn't right
    }
}


TEST_CASE("Variable set value - type text", "[VARIABLE][TEXT]") {
    const char* toasty_text = "toasty text";
    KoiScript::Runtime::Variable variable(toasty_text);

    CHECK(variable.get_type() == KoiScript::SCRIPTING_BASIC_TYPE_TEXT);
    CHECK(variable.get_size() == std::strlen(toasty_text));

    SECTION("void") {
        variable.set_value_void();
        CHECK_FALSE(variable.get_bool());
        CHECK(variable.get_char() == '\0');
        CHECK(variable.get_int() == 0);
        CHECK(variable.get_float() == 0.0f);
        CHECK(variable.get_string() == KoiScript::Runtime::Variable::VOID_STRING);
        CHECK(variable.get_c_string() == nullptr);
    }

    SECTION("bool") {
        variable.set_value(true);
        CHECK(variable.get_bool());
        CHECK(variable.get_type() == KoiScript::SCRIPTING_BASIC_TYPE_BOOL);
        CHECK(variable.get_size() == sizeof(bool));
    }

    SECTION("char") {
        char expected = 'a';
        variable.set_value(expected);
        CHECK(variable.get_char() == expected);
        CHECK(variable.get_type() == KoiScript::SCRIPTING_BASIC_TYPE_TEXT);
        CHECK(variable.get_size() == 1u);
    }

    SECTION("int") {
        int expected = 8;
        variable.set_value(expected);
        CHECK(variable.get_int() == expected);
        CHECK(variable.get_type() == KoiScript::SCRIPTING_BASIC_TYPE_INT);
        CHECK(variable.get_size() == sizeof(int));
    }

    SECTION("float") {
        float expected = 8.14f;
        variable.set_value(expected);
        CHECK(variable.get_float() == expected);
        CHECK(variable.get_type() == KoiScript::SCRIPTING_BASIC_TYPE_FLOAT);
        CHECK(variable.get_size() == sizeof(float));
    }

    SECTION("text") {
        const char* expected = "toasty text";
        variable.set_value(expected);
        CHECK(variable.get_string() == expected);
        CHECK(variable.get_type() == KoiScript::SCRIPTING_BASIC_TYPE_TEXT);
        CHECK(variable.get_size() == std::strlen(expected));
    }
}


int main( int argc, char* argv[] ) {
    // your setup ...

    int result = Catch::Session().run( argc, argv );

    // your clean-up...

    return result;
}
