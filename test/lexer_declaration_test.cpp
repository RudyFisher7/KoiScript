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


#include "scripting/lexer.hpp"
#include "scripting/extensions/extensions.hpp"

#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

#include <string>
#include <iostream>
#include <limits>
#include <vector>


namespace KoiScript = Koi::Scripting;

KoiScript::Lexer lexer;


TEST_CASE("Declare var", "[META][DECLARATION][VAR][VALID_INPUT]") {
    std::string source_code;
    std::vector<KoiScript::Token> expected;

    std::vector<KoiScript::Token> tokens;

    KoiScript::Lexer::Error error = KoiScript::Lexer::SCRIPTING_LEXER_ERROR_OK;

    SECTION("Base case") {
        source_code = "var<easy_enough>:bool;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAR_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Whitespace") {
        source_code = "\r\n var < easy\r\n \t _enoug h \t> : bo ol ; ";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAR_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type int") {
        source_code = "var<easy_enough>:int;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAR_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_INT, "int"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type float") {
        source_code = "var<easy_enough>:float;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAR_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_FLOAT, "float"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type text") {
        source_code = "var<easy_enough>:text;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAR_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_TEXT, "text"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type bool[]") {
        source_code = "var<easy_enough>:bool[];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAR_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type int[]") {
        source_code = "var<easy_enough>:int[];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAR_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_INT, "int"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type float[]") {
        source_code = "var<easy_enough>:float[];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAR_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_FLOAT, "float"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type text[]") {
        source_code = "var<easy_enough>:text[];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAR_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_TEXT, "text"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type bool[1]") {
        source_code = "var<easy_enough>:bool[1];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAR_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_INT, "1"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type bool[2]") {
        source_code = "var<easy_enough>:bool[2];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAR_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_INT, "2"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type bool[9]") {
        source_code = "var<easy_enough>:bool[9];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAR_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_INT, "9"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type bool[10]") {
        source_code = "var<easy_enough>:bool[10];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAR_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_INT, "10"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type bool[999]") {
        source_code = "var<easy_enough>:bool[999];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAR_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_INT, "999"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type bool[max int]") {
        constexpr int max = std::numeric_limits<int>::max();
        source_code = "var<easy_enough>:bool[" + std::to_string(max) + "];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAR_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_INT, std::to_string(max)),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    CHECK(error == KoiScript::Lexer::SCRIPTING_LEXER_ERROR_OK);
    REQUIRE(tokens.size() == expected.size());
    std::cout << tokens << std::endl;
    std::cout << "==== vs ====" << std::endl;
    std::cout << expected << std::endl;
    for (unsigned int i = 0; i < tokens.size(); ++i) {
        CHECK(tokens.at(i) == expected.at(i));
    }

    std::cout << source_code << std::endl;
}


TEST_CASE("Declare fun", "[META][DECLARATION][FUN][VALID_INPUT]") {
    std::string source_code;
    std::vector<KoiScript::Token> expected;

    std::vector<KoiScript::Token> tokens;

    KoiScript::Lexer::Error error = KoiScript::Lexer::SCRIPTING_LEXER_ERROR_OK;

    SECTION("Base case") {
        source_code = "fun<easy_enough>:()bool;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_FUN_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Whitespace") {
        source_code = " f un< eas y_en\tou gh>: ( \t)bo ol; \n\r\n";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_FUN_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Type ()int") {
        source_code = "fun<easy_enough>:()int;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_FUN_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_INT, "int"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Type ()void") {
        source_code = "fun<easy_enough>:()void;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_FUN_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_VOID, "void"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Type (bool)void") {
        source_code = "fun<easy_enough>:(bool)void;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_FUN_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_VOID, "void"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Type (bool,int)float") {
        source_code = "fun<easy_enough>:(bool,int)float;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_FUN_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SEPARATOR, ","),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_INT, "int"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_FLOAT, "float"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Type (bool[],int)float") {
        source_code = "fun<easy_enough>:(bool[],int)float;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_FUN_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SEPARATOR, ","),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_INT, "int"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_FLOAT, "float"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Type (bool,int[])float") {
        source_code = "fun<easy_enough>:(bool,int[])float;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_FUN_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SEPARATOR, ","),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_INT, "int"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_FLOAT, "float"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Type (bool[],int[])float") {
        source_code = "fun<easy_enough>:(bool[],int[])float;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_FUN_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SEPARATOR, ","),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_INT, "int"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SPECIFIER_FLOAT, "float"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EOF, false),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    CHECK(error == KoiScript::Lexer::SCRIPTING_LEXER_ERROR_OK);
    REQUIRE(tokens.size() == expected.size());
    std::cout << tokens << std::endl;
    std::cout << "==== vs ====" << std::endl;
    std::cout << expected << std::endl;
    for (unsigned int i = 0; i < tokens.size(); ++i) {
        CHECK(tokens.at(i) == expected.at(i));
    }

    std::cout << source_code << std::endl;
}


int main( int argc, char* argv[] ) {
    // your setup ...

    int result = Catch::Session().run( argc, argv );

    // your clean-up...

    return result;
}