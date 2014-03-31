%{
#include "stdafx.h"
#include "DesktopCalculator.h"
#include <stdio.h>
%}

%union {
	struct ast* a;
	double d;
}

%type <a> expr term factor
%token <d> NUMBER
%%
cmdline : {}
        | cmdline expr '\n' {printf("%lf\n>", eval_ast($2));}
		| cmdline '\n' {printf("\n");}
		;

expr : factor {$$ = $1}
     | expr '+' factor {$$ = add_ast($1, $3);}
	 | expr '-' factor {$$ = sub_ast($1, $3);}
	 ;

factor : term {$$ = $1}
       | factor '*' term {$$ = mul_ast($1, $3);}
       | factor '/' term {$$ = div_ast($1, $3);}
	   ;

term : '(' expr ')' {$$ = $2}
     | NUMBER {$$ = create_ast_from_number($1);}
     ;  
%%
