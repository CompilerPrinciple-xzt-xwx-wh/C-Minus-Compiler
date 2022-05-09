%{
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "ast.h"

%}
/*TOKEN definitions*/
DIGIT   [0-9]
ID      [a-z][a-z0-9]*
/*REGULAR EXPRESSIONS defining the tokens*/
%%

%%