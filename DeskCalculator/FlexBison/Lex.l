%{
#include <string>
#include "deskcalculator.h"
#include "FlexBison/Yacc.tab.hh"
#define YY_ALWAYS_INTERACTIVE 1
extern void yyerror(char *s, ...);
#define YY_DECL int yylex(yy::parser::semantic_type *lvalp, desk_calculator *calc)
%}

%option noyywrap nodefault interactive yylineno

%%
[0-9]+ |
\.[0-9]+ |
[0-9]+\.[0-9]* {lvalp->d = atof(yytext); return yy::parser::token_type::NUMBER;}

"+"  |
"-"  |
"*"  |
"/"  |
"("  |
")"  |
"{"  |
"}"  |
"="  |
";"  |
"\n" {return yytext[0];}

">" {return yy::parser::token_type::CMP_G;}
">=" {return yy::parser::token_type::CMP_GE;}
"==" {return yy::parser::token_type::CMP_EQ;}
"<" {return yy::parser::token_type::CMP_L;}
"<=" {return yy::parser::token_type::CMP_LE;}
"if" {return yy::parser::token_type::IF;}
"while" {return yy::parser::token_type::WHILE;} 

"exit" {yyterminate();}

[a-zA-Z]+ {std::string *t = new std::string(yytext, yyleng); lvalp->n = t->c_str(); return yy::parser::token_type::SYMBOL;}

[ \t] {}

. {yyerror("invalid symbol %c", yytext[0]);}
%%

