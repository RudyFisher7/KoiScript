/* decl.l */
/*  Definition section  */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* token types */
enum yytokentype {
   CHAR = 258,
   INT,
   FLOAT,
   ASTERISK,
   LEFT_PARENTHESIS,
   RIGHT_PARENTHESIS,
   LEFT_BRACKET,
   RIGHT_BRACKET,
   NAME,
   SEMICOLON,
};

int num_lines = 0;

%}

%%

   /* Rules section  */
[\t ]+         /* ignore whitespace */
char    return CHAR;
int     return INT;
float   return FLOAT;
\*      return ASTERISK;
\(      return LEFT_PARENTHESIS;
\)      return RIGHT_PARENTHESIS;
\[      return LEFT_BRACKET;
\]      return RIGHT_BRACKET;
[a-zA-Z][a-zA-Z0-9]* return NAME;
;       return SEMICOLON;
\n      num_lines++;
%%

/* User code section */
int yywrap() {}
int main (int argc, char **argv)
{
    int token;

    while (token = yylex ()) {
        switch (token) {
            case CHAR: printf ("CHAR\n");
                       break;
            case INT: printf ("INT\n");
                       break;
            case FLOAT: printf ("FLOAT\n");
                       break;
            case ASTERISK: printf ("ASTERISK\n");
                       break;
            case LEFT_PARENTHESIS: printf ("LEFT_PARENTHESIS\n");
                       break;
            case RIGHT_PARENTHESIS: printf ("RIGHT_PARENTHESIS\n");
                       break;
            case LEFT_BRACKET: printf ("LEFT_BRACKET\n");
                       break;
            case RIGHT_BRACKET: printf ("RIGHT_BRACKET\n");
                       break;
            case NAME: printf ("NAME: %s\n", yytext);
                       break;
            case SEMICOLON: printf ("SEMICOLON\n\n");
                       break;
            default:  printf ("Unexpected token\n");
        }
    }
    printf ("Number of lines scanned: %d\n", num_lines);
}