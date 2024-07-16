

#include "scripting/lexer.hpp"

#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

#include <string>
#include <iostream>
#include <limits>
#include <vector>


namespace KoiScript = Koi::Scripting;

KoiScript::Lexer lexer;


TEST_CASE("Declare var", "[VAR][VALID_INPUT]") {
    std::string source_code;
    std::vector<KoiScript::Token> expected;

    std::vector<KoiScript::Token> tokens;

    KoiScript::Lexer::Error error = KoiScript::Lexer::SCRIPTING_LEXER_ERROR_OK;

    SECTION("Base case") {
        source_code = "var<easy_enough>:bool;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Whitespace") {
        source_code = " var\t < easy _enoug h >\n\r\n : bo ol ; ";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("var is id") {
        source_code = "var<var>:bool;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("bool is id") {
        source_code = "var<bool>:bool;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type int") {
        source_code = "var<easy_enough>:int;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "int"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type float") {
        source_code = "var<easy_enough>:float;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "float"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type text") {
        source_code = "var<easy_enough>:text;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "text"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type bool[]") {
        source_code = "var<easy_enough>:bool[];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type int[]") {
        source_code = "var<easy_enough>:int[];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "int"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type float[]") {
        source_code = "var<easy_enough>:float[];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "float"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type text[]") {
        source_code = "var<easy_enough>:text[];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "text"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type bool[1]") {
        source_code = "var<easy_enough>:bool[1];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE, "1"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type bool[2]") {
        source_code = "var<easy_enough>:bool[2];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE, "2"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type bool[9]") {
        source_code = "var<easy_enough>:bool[9];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE, "9"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type bool[10]") {
        source_code = "var<easy_enough>:bool[10];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE, "10"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type bool[999]") {
        source_code = "var<easy_enough>:bool[999];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE, "999"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("type bool[max int]") {
        constexpr int max = std::numeric_limits<int>::max();
        source_code = "var<easy_enough>:bool[" + std::to_string(max) + "];";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "var"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE, std::to_string(max)),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    CHECK(error == KoiScript::Lexer::SCRIPTING_LEXER_ERROR_OK);
    REQUIRE(tokens.size() == expected.size());
    for (unsigned int i = 0; i < tokens.size(); ++i) {
        std::cout << tokens.at(i) << std::endl;
        CHECK(tokens.at(i) == expected.at(i));
    }
}


TEST_CASE("Declare fun", "[FUN][VALID_INPUT]") {
    std::string source_code;
    std::vector<KoiScript::Token> expected;

    std::vector<KoiScript::Token> tokens;

    KoiScript::Lexer::Error error = KoiScript::Lexer::SCRIPTING_LEXER_ERROR_OK;

    SECTION("Base case") {
        source_code = "fun<easy_enough>:()bool;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Whitespace") {
        source_code = "\r\n\tf un< eas y_en\r\nough>\t: ( )bo ol; ";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Type ()int") {
        source_code = "fun<easy_enough>:()int;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "int"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Type ()void") {
        source_code = "fun<easy_enough>:()void;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "void"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Type (bool)void") {
        source_code = "fun<easy_enough>:(bool)void;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "void"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Type (bool,int)float") {
        source_code = "fun<easy_enough>:(bool,int)float;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SEPARATOR, ","),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "int"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "float"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Type (bool[],int)float") {
        source_code = "fun<easy_enough>:(bool[],int)float;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SEPARATOR, ","),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "int"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "float"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Type (bool,int[])float") {
        source_code = "fun<easy_enough>:(bool,int[])float;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SEPARATOR, ","),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "int"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "float"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Type (bool[],int[])float") {
        source_code = "fun<easy_enough>:(bool[],int[])float;";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_LEFT_META, "fun"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SEPARATOR, ","),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "int"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START, "["),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END, "]"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "float"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    CHECK(error == KoiScript::Lexer::SCRIPTING_LEXER_ERROR_OK);
    REQUIRE(tokens.size() == expected.size());
    for (unsigned int i = 0; i < tokens.size(); ++i) {
        std::cout << tokens.at(i) << std::endl;
        CHECK(tokens.at(i) == expected.at(i));
    }
}


int main( int argc, char* argv[] ) {
    // your setup ...

    int result = Catch::Session().run( argc, argv );

    // your clean-up...

    return result;
}