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
letter   [a-zA-Z]
ID      {letter}({digit}|{letter}|"_")*

ICONST   "0"|[1-9]{digit}*
FCONST   "0"|[1-9]{digit}*"."{digit}+
CCONST   \'.\'|\'\\.\'  
SCONST   \"(\\.|[^"\\])*\"

COMMENT ("/*"([^\*]|(\*)*[^\*/])*(\*)*"*\")|("//"[^\n]*)

/*REGULAR EXPRESSIONS defining the tokens*/
%%
"+"               {yylval.node = new Node(yytext, "PLUS", 0); return PLUS;}
"-"               {yylval.node = new Node(yytext, "MINUS", 0); return MINUS;}
"*"               {yylval.node = new Node(yytext, "MUL", 0); return MUL;}
"/"               {yylval.node = new Node(yytext, "DIV", 0); return DIV;}
"%"               {yylval.node = new Node(yytext, "MOD", 0); return MOD;}
"="               {yylval.node = new Node(yytext, "ASSIGN", 0); return ASSIGN;}
"++"              {yylval.node = new Node(yytext, "INCR_P", 0); return INCR_P;}
"--"              {yylval.node = new Node(yytext, "INCR_M", 0); return INCR_M;}
"&&"              {yylval.node = new Node(yytext, "AND", 0); return AND;}
"||"              {yylval.node = new Node(yytext, "OR", 0); return OR;}
"!"               {yylval.node = new Node(yytext, "NOT", 0); return NOT;}
"=="              {yylval.node = new Node(yytext, "EQUAL", 0); return EQUAL;}
"!="              {yylval.node = new Node(yytext, "NOTEQUAL", 0); return NOTEQUAL;}
">"               {yylval.node = new Node(yytext, "GT", 0); return GT;}
">="              {yylval.node = new Node(yytext, "GE", 0); return GE;}
"<"               {yylval.node = new Node(yytext, "LT", 0); return LT;}
"<="              {yylval.node = new Node(yytext, "LE", 0); return LE;}
"&"               {yylval.node = new Node(yytext, "ADDRESS", 0); return ADDRESS;}

"("               {yylval.node = new Node(yytext, "OPENPAREN", 0); return OPENPAREN;}
")"               {yylval.node = new Node(yytext, "CLOSEPAREN", 0); return CLOSEPAREN;}
"["               {yylval.node = new Node(yytext, "OPENBRACKET", 0); return OPENBRACKET;}
"]"               {yylval.node = new Node(yytext, "CLOSEBRACKET", 0); return CLOSEBRACKET;}
"{"               {yylval.node = new Node(yytext, "OPENCURLY", 0); return OPENCURLY;}
"}"               {yylval.node = new Node(yytext, "CLOSECURLY", 0); return CLOSECURLY;}
","               {yylval.node = new Node(yytext, "COMMA", 0); return COMMA;}
"."               {yylval.node = new Node(yytext, "DOT", 0); return DOT;}
";"               {yylval.node = new Node(yytext, "SEMI", 0); return SEMI;}

"char"            {yylval.node = new Node(yytext, "CHAR", 0); return CHAR;}
"int"             {yylval.node = new Node(yytext, "INT", 0); return INT;}
"float"           {yylval.node = new Node(yytext, "FLOAT", 0); return FLOAT;}
"double"          {yylval.node = new Node(yytext, "DOUBLE", 0); return DOUBLE;}
"void"            {yylval.node = new Node(yytext, "VOID", 0); return VOID;}
"if"              {yylval.node = new Node(yytext, "IF", 0); return IF;}
"else"            {yylval.node = new Node(yytext, "ELSE", 0); return ELSE;}
"for"             {yylval.node = new Node(yytext, "FOR", 0); return FOR;}
"while"           {yylval.node = new Node(yytext, "WHILE", 0); return WHILE;}
"continue"        {yylval.node = new Node(yytext, "CONTINUE", 0); return CONTINUE;}
"break"           {yylval.node = new Node(yytext, "BREAK", 0); return BREAK;}
"return"          {yylval.node = new Node(yytext, "RETURN", 0); return RETURN;}

{ID}              {yylval.node = new Node(yytext, "ID", 0); return ID;}
{ICONST}          {yylval.node = new Node(yytext, "Integer", 0); return Integer;}
{FCONST}          {yylval.node = new Node(yytext, "Realnumber", 0); return Realnumber;}
{CCONST}          {yylval.node = new Node(yytext, "Character", 0); return Character;}
{SCONST}          {yylval.node = new Node(yytext, "String", 0); return String;}
{COMMENT}         { ;}
"\n"              {lineno = lineno + 1;}
"\t"              { ;}
.                 {yyerror("Unrecognized character: %s\n", yytext);}
%%