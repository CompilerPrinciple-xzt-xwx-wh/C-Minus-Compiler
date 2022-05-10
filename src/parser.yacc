/*
 * @Author: xwxr
 * @Date: 2022-05-09 20:00:51
 * @LastEditors: xwxr
 * @LastEditTime: 2022-05-10 18:40:23
 * @Description: C-Minus Grammar Generator
 */

%{
    #include <stdio.h>
    #include "ast.h"
    #include "type.h"
    int yylex(void);
    int mistakeRecord[4096]={0};
    int mistake = 0;
    extern Node *ROOT;
    void yyerror (char const *s) {
        fprintf (stderr, "%s\n", s);
    }
%}

/*declared types*/
%union
{
    struct Node* node;
}
%token <node> CHAR INT FLOAT DOUBLE VOID
%token <node> IF ELSE FOR WHILE CONTINUE BREAK RETURN
%token <node> ID
%token <node> COMMA DOT SEMI
%token <node> PLUS MINUS MUL DIV MOD
%token <node> ASSIGN
%token <node> INCR
%token <node> AND OR NOT
%token <node> EQUAL NOTEQUAL GT GE LT LE
%token <node> OPENPAREN CLOSEPAREN OPENBRACKET CLOSEBRACKET OPENCURLY CLOSECURLY

%nonassoc INCR
%nonassoc ELSE

%right ASSIGN
%left OR
%left AND
%left EQUAL NOTEQUAL GT GE LT LE
%left PLUS MINUS
%left MUL DIV MOD
%right NOT
%left OPENPAREN CLOSEPAREN OPENBRACKET CLOSEBRACKET

%type <node> Program GlobalDefinitionList GlobalDefinition Typer
%type <node> GlobalVariableList GlobalVariable Function ParameterList Parameter
%type <node> FunctionCode Instruction Definition LocalVariableList LocalVariable
%type <node> Statement Expression Arguments

%%
Program:
    GlobalDefinitionList {
        $$ = new Node("", "Program", 1, $1);
        ROOT = $$;
    }
    ;

GlobalDefinitionList:
    GlobalDefinition GlobalDefinitionList {
        $$ = new Node("", "GlobalDefinitionList", 2, $1, $2);
    }
    | %empty {
        $$ = nullptr;
    }
    ;

GlobalDefinition:
    Typer GlobalVariableList SEMI {
        $$ = new Node("", "GlobalDefinition", 3, $1, $2, $3);
    }
    | Typer Function SEMI {
        $$ = new Node("", "GlobalDefinition", 3, $1, $2, $3);
    }
    ;

GlobalVariableList:
    GlobalVariable COMMA GlobalVariableList {
        $$ = new Node("", "GlobalVariableList", 3, $1, $2, $3);
    }
    | GlobalVariable {
        $$ = new Node("", "GlobalVariableList", 1, $1);
    }
    ;

Typer:
    CHAR {
        $$ = new Node("", "Typer", 1, $1);
    }
    | INT {
        $$ = new Node("", "Typer", 1, $1);
    }
    | FLOAT {
        $$ = new Node("", "Typer", 1, $1);
    }
    | DOUBLE {
        $$ = new Node("", "Typer", 1, $1);
    }
    | VOID {
        $$ = new Node("", "Typer", 1, $1);
    }
    ;

GlobalVariable:
    ID {
        $$ = new Node("", "GlobalVariable", 1, $1);
    }
    | ID OPENBRACKET INT CLOSEBRACKET {
        $$ = new Node("", "GlobalVariable", 4, $1, $2, $3, $4);
    }
    ;

Function:
    ID OPENPAREN ParameterList CLOSEPAREN OPENCURLY FunctionCode CLOSECURLY {
        $$ = new Node("", "Function", 7, $1, $2, $3, $4, $5, $6, $7);
    }
    ;

ParameterList:
    Parameter COMMA ParameterList {
        $$ = new Node("", "ParameterList", 3, $1, $2, $3);
    }
    | Parameter {
        $$ = new Node("", "ParameterList", 1, $1);
    }
    | VOID {
        $$ = new Node("", "ParameterList", 1, $1);
    }
    | %empty {
        $$ = nullptr;
    }
    ;
    
Parameter:
    Typer LocalVariable {
        $$ = new Node("", "Parameter", 2, $1, $2);
    }
    ;

FunctionCode:


Instruction:


Definition:
    Typer LocalVariableList SEMI{
        $$ = new Node("", "Definition", 3, $1, $2, $3);
    }
    ;

LocalVariableList:
    LocalVariable COMMA LocalVariableList {
        $$ = new Node("", "LocalVariableList", 3, $1, $2, $3);
    }
    | LocalVariable {
        $$ = new Node("", "LocalVariableList", 1, $1);
    }
    ;

LocalVariable:
    ID {
        $$ = new Node("", "LocalVariable", 1, $1);
    }
    | ID OPENBRACKET INT CLOSEBRACKET {
        $$ = new Node("", "LocalVariable", 4, $1, $2, $3, $4);
    }
    | ID OPENBRACKET CLOSEBRACKET {
        $$ = new Node("", "LocalVariable", 3, $1, $2, $3);
    }
    ;

Statement:


Expression:
    Expression ASSIGN Expression {
        $$ = new Node("", "Expression", 3, $1, $2, $3);
        $$->setValueType($3->getValueType());
    }
    | Expression AND Expression {

    }
    | Expression OR Expression {

    }
    | NOT Expression {

    }
    | INCR Expression {

    }
    | Expression INCR {

    }
    | Expression PLUS Expression {

    }
    | Expression MINUS Expression {

    }
    | Expression MUL Expression {

    }
    | Expression DIV Expression {

    }
    | Expression MOD Expression {

    }
    | Expression EQUAL Expression {

    }
    | Expression NOTEQUAL Expression {

    }
    | Expression GT Expression {

    }
    | Expression GE Expression {

    }
    | Expression LT Expression {

    }
    | Expression LE Expression {

    }
    | OPENPAREN Expression CLOSEPAREN {

    }
    | MINUS Expression {

    }






Arguments:



%%