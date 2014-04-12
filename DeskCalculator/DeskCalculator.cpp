// DeskCalculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "assert.h"
#include "DeskCalculator.h"
#include "context.h"
#include "FlexBison\yacc.tab.hh"
#include <stdarg.h>
#include <string>

extern int yylineno;

class desk_calculator_impl
{
public:
	desk_calculator_impl()
	{
		global_context_ = new_context(0);
		toplevel_context_ = global_context_;
	}

	~desk_calculator_impl()
	{
		destroy_context(toplevel_context_);
	}

	struct context* get_global_context()
	{
		return global_context_;
	}

	struct context* get_toplevel_context()
	{
		return toplevel_context_;
	}

private:
	struct context* global_context_;
	struct context* toplevel_context_;
};

desk_calculator::desk_calculator()
{
	impl_ = new desk_calculator_impl();
}

desk_calculator::~desk_calculator()
{
	delete impl_;
}

struct context* desk_calculator::get_global_context()
{
	return impl_->get_global_context();
}

struct context* desk_calculator::get_toplevel_context()
{
	return impl_->get_toplevel_context();
}

void yy::parser::error(const location_type& loc, const std::string& msg)
{

}

int _tmain(int argc, _TCHAR* argv[])
{
	yylineno = 0;
	desk_calculator* calc = new desk_calculator;
	yy::parser p(calc);
	p.parse();
	return 0;
}

void yyerror(char *s, ...)
{
	va_list ap;
	va_start(ap, s);
	fprintf(stderr, "%d: error: ", yylineno);
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}

