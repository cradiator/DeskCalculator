%{
#include "stdafx.h"
#include "FlexBison/Yacc.yy.c"
%}

%option noyywrap nodefault 
%%
[0-9]+ |
\.[0-9]+ |
[0-9]+\.[0-9]* {yylval.d = atof(yytext); return NUMBER}

"+" |
"-" |
"*" |
"/" |
"(" |
")" |
"\n" {return yytext[0];}

[ \t] {}

. {printf("error symbol %c", yytext[0]);}
%%
