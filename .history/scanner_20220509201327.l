%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ast.h"

int lineno = 1;
void yyerror();
%}
/*TOKEN definitions*/
digit   [0-9]
alpha   [a-zA-Z]
ID      {alpha}({digit}|{alpha}|"_")*


/*REGULAR EXPRESSIONS defining the tokens*/
%%
"+"               {retun PLUS;}
"-"               {return MINUS;}
"*"               {return MUL;}
"/"               {return DIV;}
"%"               {return MOD;}
"="               {return ASSIGN;}
"++"|"--"         {return INCR;}
"&&"              {return AND;}
"||"              {return OR;}
"!"               {return NOT;}
"=="              {return EQUAL;}
"!="              {return UNEQUAL;}
">"               {return GT;}
">="              {return GE;}
"<"               {return LT;}
"<="              {return LE;}

"("               {return LPAREN;}
")"               {return RPAREN;}
"]"               {return LBRACK;}
"["               {return RBRACK;}
"{"               {return LBRACE;}
"}"               {return RBRACE;}
","               {return COMMA;}
"."               {return DOT;}
";"               {return SEMI;}


.                 {}
%%