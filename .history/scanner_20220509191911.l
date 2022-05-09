%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ast.h"

%}
/*TOKEN definitions*/
digit   [0-9]
alpha   [a-zA-Z]

ID      {alpha}({digit}|{alpha}|{_})*



/*REGULAR EXPRESSIONS defining the tokens*/
%%

%%