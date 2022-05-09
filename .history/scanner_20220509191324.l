%{
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "ast.h"

%}
/*TOKEN definitions*/
digit   [0-9]
alpha   [a-zA-Z]
alnum   {digit}|{alpha}|{_}

ID      {alpha}+{alnum}*



/*REGULAR EXPRESSIONS defining the tokens*/
%%

%%