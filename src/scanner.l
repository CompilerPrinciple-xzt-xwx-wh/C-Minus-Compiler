%option yylineno
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ast.h"
#include "parser.hpp"

int lineno = 1;
void yyerror(const char*);
%}
/*TOKEN definitions*/
digit   [0-9]
letter   [a-zA-Z]
ID      {letter}({digit}|{letter}|"_")*

ICONST   "0"|[1-9]{digit}*
FCONST   "0"|{digit}*"."{digit}+
CCONST   \'.\'|\'\\.\'  
SCONST   \"(\\.|[^"\\])*\"

COMMENT ("//"[^\n]*)

/*REGULAR EXPRESSIONS defining the tokens*/
%%
"+"               {yylval.node = new Node( lineno, yytext, "PLUS"); return PLUS;}
"-"               {yylval.node = new Node( lineno, yytext, "MINUS"); return MINUS;}
"*"               {yylval.node = new Node( lineno, yytext, "MUL"); return MUL;}
"/"               {yylval.node = new Node( lineno, yytext, "DIV"); return DIV;}
"%"               {yylval.node = new Node(lineno, yytext, "MOD"); return MOD;}
"="               {yylval.node = new Node(lineno, yytext, "ASSIGN" ); return ASSIGN;}
"++"              {yylval.node = new Node(lineno, yytext, "INCR_P"); return INCR_P;}
"--"              {yylval.node = new Node(lineno, yytext, "INCR_M"); return INCR_M;}
"&&"              {yylval.node = new Node(lineno, yytext, "AND"); return AND;}
"||"              {yylval.node = new Node(lineno, yytext, "OR"); return OR;}
"!"               {yylval.node = new Node(lineno, yytext, "NOT"); return NOT;}
"=="              {yylval.node = new Node(lineno, yytext, "EQUAL"); return EQUAL;}
"!="              {yylval.node = new Node(lineno, yytext, "NOTEQUAL"); return NOTEQUAL;}
">"               {yylval.node = new Node(lineno, yytext, "GT"); return GT;}
">="              {yylval.node = new Node(lineno, yytext, "GE"); return GE;}
"<"               {yylval.node = new Node(lineno, yytext, "LT"); return LT;}
"<="              {yylval.node = new Node(lineno, yytext, "LE"); return LE;}
"&"               {yylval.node = new Node(lineno, yytext, "ADDRESS"); return ADDRESS;}

"("               {yylval.node = new Node(lineno, yytext, "OPENPAREN"); return OPENPAREN;}
")"               {yylval.node = new Node(lineno, yytext, "CLOSEPAREN"); return CLOSEPAREN;}
"["               {yylval.node = new Node(lineno, yytext, "OPENBRACKET"); return OPENBRACKET;}
"]"               {yylval.node = new Node(lineno, yytext, "CLOSEBRACKET"); return CLOSEBRACKET;}
"{"               {yylval.node = new Node(lineno, yytext, "OPENCURLY"); return OPENCURLY;}
"}"               {yylval.node = new Node(lineno, yytext, "CLOSECURLY"); return CLOSECURLY;}
","               {yylval.node = new Node(lineno, yytext, "COMMA"); return COMMA;}
";"               {yylval.node = new Node(lineno, yytext, "SEMI"); return SEMI;}

"char"            {yylval.node = new Node(lineno, yytext, "CHAR"); return CHAR;}
"int"             {yylval.node = new Node(lineno, yytext, "INT"); return INT;}
"float"           {yylval.node = new Node(lineno, yytext, "FLOAT"); return FLOAT;}
"double"          {yylval.node = new Node(lineno, yytext, "DOUBLE"); return DOUBLE;}
"void"            {yylval.node = new Node(lineno, yytext, "VOID"); return VOID;}
"if"              {yylval.node = new Node(lineno, yytext, "IF"); return IF;}
"else"            {yylval.node = new Node(lineno, yytext, "ELSE"); return ELSE;}
"for"             {yylval.node = new Node(lineno, yytext, "FOR"); return FOR;}
"while"           {yylval.node = new Node(lineno, yytext, "WHILE"); return WHILE;}
"continue"        {yylval.node = new Node(lineno, yytext, "CONTINUE"); return CONTINUE;}
"break"           {yylval.node = new Node(lineno, yytext, "BREAK"); return BREAK;}
"return"          {yylval.node = new Node(lineno, yytext, "RETURN"); return RETURN;}

{ID}              {yylval.node = new Node(lineno, yytext, "ID"); return ID;}
{ICONST}          {yylval.node = new Node(lineno, yytext, "Integer"); return Integer;}
{FCONST}          {yylval.node = new Node(lineno, yytext, "Realnumber"); return Realnumber;}
{CCONST}          {yylval.node = new Node(lineno, yytext, "Character"); return Character;}
{SCONST}          {yylval.node = new Node(lineno, yytext, "String"); return String;}
{COMMENT}         { ;}
"\n"              {lineno = lineno + 1;}
"\t"              { ;}
" "               { }
%%

int yywrap(){
    return 1; 
}