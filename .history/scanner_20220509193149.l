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
"("               {return LP;}
%%