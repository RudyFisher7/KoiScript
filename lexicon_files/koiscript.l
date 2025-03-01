/*
 * Sample Scanner1:
 * Description: Replace the string "username" from standard input
 *              with the user's login name (e.g. lgao)
 * Usage: (1) $ flex sample1.lex
 *        (2) $ gcc lex.yy.c -lfl
 *        (3) $ ./a.out
 *            stdin> username
 *	      stdin> Ctrl-D
 * Question: What is the purpose of '%{' and '%}'?
 *           What else could be included in this section?
 */

%{
/* need this for the call to getlogin() below */
#include <unistd.h>
%}

%%
[a-zA-Z]+   { return 1; }
[0-9]+      { return 2; }
[ \t]+      { }
%%
int yywrap(){ return 1; }
main()
{
  yylex();
}