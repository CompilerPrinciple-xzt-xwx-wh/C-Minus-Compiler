/*
* @file ast.h
* @brief Definition of Node's structure and essential declarations of Node's API for Parsing
* @author Wang Hui (3190105609@zju.edu.cn)
* @version 1.0
* @date 2022-05-09
* @copyright Copyright (c) 2022. Xu Zhengtao,Wang Hui and Xie Wenxiang. 
* 
*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ast.h"

int lineno = 1;
%}
/*TOKEN definitions*/
digit   [0-9]
alpha   [a-zA-Z]
ID      {alpha}({digit}|{alpha}|"_")*


/*REGULAR EXPRESSIONS defining the tokens*/
%%
"+"               {retun PLUS;}
"-"                

"("               {return LPAREN;}
")"               {return RPAREN;}
%%