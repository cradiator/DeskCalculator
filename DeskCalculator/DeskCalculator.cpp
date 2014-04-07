// DeskCalculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "assert.h"
#include "DesktopCalculator.h"
extern "C" int yyparse();
extern "C" int yylineno;

int _tmain(int argc, _TCHAR* argv[])
{
    yylineno = 0;
    printf(">");
    yyparse();
	return 0;
}

