%{
#include "DesktopCalculator.h"
#include "ast.h"
#include "context.h"
#include <stdio.h>
#include <stdarg.h>

extern int yylineno;
extern int yylex();
void yyerror(char *s, ...);

%}

%union {
	struct ast* a;
	struct ast_list* al;
	double d;
	const char* n;
}

%type <a> stat expr assign cmp add_sub mul_div sym_number
%type <al> stat_list
%token <d> NUMBER
%token <n> SYMBOL
%token CMP_L CMP_LE CMP_EQ CMP_G CMP_GE
%token IF WHILE

%right '='
%left CMP_L CMP_LE CMP_EQ CMP_G CMP_GE
%left '+' '-'
%left '*' '/'

%%

start : {}
      | start stat '\n' {print_ast($2);}
	  ;

stat_list : {$$ = new_ast_list();}
          | stat_list stat ';' {$$ = add_ast_to_ast_list($1, $2);}
		  ;

stat : expr {$$ = $1}
     | IF '(' expr ')' '{' stat_list '}' {$$ = new_cond_ast(NODE_COND_IF, $3, $6);}
	 | WHILE '(' expr ')' '{' stat_list '}' {$$ = new_cond_ast(NODE_COND_WHILE, $3, $6);}
	 ;

expr : assign {$$ = $1;}
     | cmp {$$ = $1;}
	 ;

assign : SYMBOL '=' cmp {$$ = new_op2_ast(NODE_OP2_ASSIGN, $1, $3);}
       ;
	   
cmp : cmp CMP_L add_sub {$$ = new_op2_ast(NODE_OP2_L, $1, $3);}
    | cmp CMP_LE add_sub {$$ = new_op2_ast(NODE_OP2_LE, $1, $3);}
	| cmp CMP_EQ add_sub {$$ = new_op2_ast(NODE_OP2_EQ, $1, $3);}
	| cmp CMP_G add_sub {$$ = new_op2_ast(NODE_OP2_G, $1, $3);}
	| cmp CMP_GE add_sub {$$ = new_op2_ast(NODE_OP2_GE, $1, $3);}
	| add_sub {$$ = $1;}
	;
	
add_sub : add_sub '+' mul_div {$$ = new_op2_ast(NODE_OP2_ADD, $1, $3);}
        | add_sub '-' mul_div {$$ = new_op2_ast(NODE_OP2_SUB, $1, $3);}
		| mul_div {$$ = $1}
		;
		
mul_div : mul_div '*' sym_number {$$ = new_op2_ast(NODE_OP2_MUL, $1, $3);}
        | mul_div '/' sym_number {$$ = new_op2_ast(NODE_OP2_DIV, $1, $3);}
		| sym_number {$$ = $1;}
		;
		
sym_number : NUMBER {$$ = new_number_ast($1);}
           | SYMBOL {$$ = new_ref_ast($1);}
		   | '(' cmp ')' {$$ = $2;}
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
