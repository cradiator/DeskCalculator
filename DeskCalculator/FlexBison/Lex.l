%{
#include "FlexBison/Yacc.tab.h"
#include "stdlib.h"
#define YY_ALWAYS_INTERACTIVE 1
extern void yyerror(char *s, ...);
%}

%option noyywrap nodefault interactive yylineno
%%
[0-9]+ |
\.[0-9]+ |
[0-9]+\.[0-9]* {yylval.d = atof(yytext); return NUMBER;}

"+"  |
"-"  |
"*"  |
"/"  |
"("  |
")"  |
"{"  |
"}"  |
"="  |
"\n" {return yytext[0];}

">" {return CMP_G;}
">=" {return CMP_GE;}
"==" {return CMP_EQ;}
"<" {return CMP_L;}
"<=" {return CMP_LE;}
"if" {return IF;}
"while" {return WHILE;} 

"exit" {yyterminate();}

[a-zA-Z]+ {yylval.n = yytext; return SYMBOL;}

[ \t] {}

. {yyerror("invalid symbol %c", yytext[0]);}
%%
