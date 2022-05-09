%option yylineno
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

COMMENT ("/*"([^\*]|(\*)*[^\*/])*(\*)*"*\")|("//"[^\n]*)

/*REGULAR EXPRESSIONS defining the tokens*/
%%
"+"               {yylval.node = new Node(yytext, "PLUS", 0); return PLUS;}
"-"               {yylval.node = new Node(yytext, "MINUS", 0); return MINUS;}
"*"               {yylval.node = new Node(yytext, "MUL", 0); return MUL;}
"/"               {yylval.node = new Node(yytext, "DIV", 0); return DIV;}
"%"               {yylval.node = new Node(yytext, "MOD", 0); return MOD;}
"="               {yylval.node = new Node(yytext, "ASSIGN", 0); return ASSIGN;}
"++"|"--"         {yylval.node = new Node(yytext, "INCR", 0); return INCR;}
"&&"              {yylval.node = new Node(yytext, "AND", 0); return AND;}
"||"              {yylval.node = new Node(yytext, "OR", 0); return OR;}
"!"               {yylval.node = new Node(yytext, "NOT", 0); return NOT;}
"=="              {yylval.node = new Node(yytext, "", 0); return EQUAL;}
"!="              {yylval.node = new Node(yytext, "", 0); return UNEQUAL;}
">"               {yylval.node = new Node(yytext, "", 0); return GT;}
">="              {yylval.node = new Node(yytext, "", 0); return GE;}
"<"               {yylval.node = new Node(yytext, "", 0); return LT;}
"<="              {yylval.node = new Node(yytext, "", 0); return LE;}

"("               {return LPAREN;}
")"               {return RPAREN;}
"]"               {return LBRACK;}
"["               {return RBRACK;}
"{"               {return LBRACE;}
"}"               {return RBRACE;}
","               {return COMMA;}
"."               {return DOT;}
";"               {return SEMI;}

"char"            {return CHAR;}
"int"             {return INT;}
"float"           {return FLOAT;}
"double"          {return DOUBLE;}
"void"            {return VOID;}
"if"              {return IF;}
"else"            {return else;}
"for"             {return FOR;}
"while"           {return WHILE;}
"continue"        {return CONTINUE;}
"break"           {return BREAK;}
"return"          {return RETURN;}

{ID}              {return ID;}
{COMMENT}         { ;}
"\n"              {lineno = lineno + 1;}
"\t"              { ;}
.                 {yyerror("Unrecognized character: %s\n", yytext);}
%%