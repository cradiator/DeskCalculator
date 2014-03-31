// DeskCalculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "assert.h"
#include "DesktopCalculator.h"

struct ast* make_ast(enum node_type type, struct ast* op1, struct ast* op2)
{
	struct ast* a = new struct ast;
	a->type   = type;
	a->lchild = op1;
	a->rchild = op2;
	return a;
}

double eval_ast(struct ast* a)
{
	if (a->type == NODE_NUMBER)
		return a->value;

	if (a->type == NODE_ADD)
		return eval_ast(a->lchild) + eval_ast(a->rchild);

	if (a->type == NODE_SUB)
		return eval_ast(a->lchild) - eval_ast(a->rchild);

	if (a->type == NODE_MUL)
		return eval_ast(a->lchild) * eval_ast(a->rchild);

	if (a->type == NODE_DIV)
		return eval_ast(a->lchild) / eval_ast(a->rchild);

	assert(false);
	return 0;
}

struct ast* add_ast(struct ast* op1, struct ast* op2)
{
	return make_ast(NODE_ADD, op1, op2);
}

struct ast* sub_ast(struct ast* op1, struct ast* op2)
{
	return make_ast(NODE_SUB, op1, op2);
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

