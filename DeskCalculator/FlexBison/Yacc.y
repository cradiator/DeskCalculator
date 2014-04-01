%{
#include "DesktopCalculator.h"
#include <stdio.h>
#include <stdarg.h>

extern int yylineno;
extern int yylex();
void yyerror(char *s, ...);

%}

%union {
	struct ast* a;
	double d;
}

%type <a> expr term factor
%token <d> NUMBER
%token EXIT
%%
cmdline : {} 
        | cmdline expr '\n' {printf("%lf\n>", eval_ast($2));}
		| cmdline '\n' {printf(">");}
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

void
yyerror(char *s, ...)
{
	va_list ap;
	va_start(ap, s);
	printf("%d: error: ", yylineno);
	vprintf(s, ap);
	printf("\n");
}
