%{
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "ast.h"

%}
/*TOKEN definitions*/
DIGIT   [0-9]
ID      [a-zA-Z][a-zA-Z0-9_]*


/*REGULAR EXPRESSIONS defining the tokens*/
%%

%%