

#include "scripting/lexer.hpp"

#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

#include <string>
#include <iostream>
#include <limits>
#include <vector>


namespace KoiScript = Koi::Scripting;

KoiScript::Lexer lexer;


TEST_CASE("Evaluation metas", "[META][EVALUATION][VALID_INPUT]") {
    std::string source_code;
    std::vector<KoiScript::Token> expected;

    std::vector<KoiScript::Token> tokens;

    KoiScript::Lexer::Error error = KoiScript::Lexer::SCRIPTING_LEXER_ERROR_OK;

    SECTION("Base case 1") {
        source_code = "val<easy_enough>();";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VAL_META, "val"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Base case 2") {
        source_code = "exe<easy_enough>();";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EXE_META, "exe"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Base case 3") {
        source_code = "ref<easy_enough>();";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_REF_META, "ref"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    // note, only exe meta can have args, so we don't care to test others with them.
    SECTION("Args 1 literal 1") {
        source_code = "exe<easy_enough>(1);";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EXE_META, "exe"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_INT, "1"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Args 1 literal 1 neg") {
        source_code = "exe<easy_enough>(-1);";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EXE_META, "exe"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_INT, "-1"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Args 1 literal 2") {
        source_code = "exe<easy_enough>(true);";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EXE_META, "exe"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_BOOL, "true"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Args 1 literal 3") {
        source_code = "exe<easy_enough>(false);";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EXE_META, "exe"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_BOOL, "false"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Args 1 literal 4") {
        source_code = "exe<easy_enough>(1.2);";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EXE_META, "exe"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_FLOAT, "1.2"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Args 1 literal 5") {
        source_code = "exe<easy_enough>(' some text\n \r here \t');";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EXE_META, "exe"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND, "'"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TEXT, " some text\n \r here \t"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND, "'"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Args 1 literal 6") {
        source_code = "exe<easy_enough>(void(bool):{  });";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EXE_META, "exe"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "void"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TYPE, "bool"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_COMBINER, ":"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SCOPE_START, "{"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SCOPE_END, "}"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Args 1 literal 7 - array") {
        source_code = "exe<easy_enough>({ -1, 4, 6, 2 });";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EXE_META, "exe"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SCOPE_START, "{"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_INT, "-1"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SEPARATOR, ","),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_INT, "4"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SEPARATOR, ","),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_INT, "6"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SEPARATOR, ","),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_INT, "2"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SCOPE_END, "}"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Args 4 literals 1") {
        source_code = "exe<easy_enough>(1, 3.9, false, 'here some text toasty');";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EXE_META, "exe"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_INT, "1"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SEPARATOR, ","),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_FLOAT, "3.9"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SEPARATOR, ","),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_BOOL, "false"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SEPARATOR, ","),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND, "'"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_TEXT, "here some text toasty"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND, "'"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    SECTION("Args complex function") {
        source_code = "exe<easy_enough>({ exe<assign>(ref<easy_enough3>(), 5); });";
        expected = {
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EXE_META, "exe"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),

                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SCOPE_START, "{"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_EXE_META, "exe"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "assign"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),

                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_REF_META, "ref"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_START, "<"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID, "easy_enough3"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_ID_END, ">"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_START, "("),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SEPARATOR, ","),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_INT, "5"),

                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_SCOPE_END, "}"),

                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_GROUPING_END, ")"),
                KoiScript::Token(KoiScript::Token::SCRIPTING_TOKEN_TYPE_DELIMITER, ";"),
        };

        error = lexer.lex(source_code.c_str(), source_code.size(), tokens);
    }

    CHECK(error == KoiScript::Lexer::SCRIPTING_LEXER_ERROR_OK);
    REQUIRE(tokens.size() == expected.size());
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