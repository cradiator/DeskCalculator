#pragma once

enum node_type {
	NODE_NUMBER = 0,
	NODE_ADD,
	NODE_SUB,
	NODE_MUL,
	NODE_DIV,
} node_type ;

struct ast {
	enum node_type type;
	union {
		struct {
			struct ast* lchild;
			struct ast* rchild;
		};

		double value;
	};
};

double eval_ast(struct ast* a);
struct ast* add_ast(struct ast* op1, struct ast* op2);
struct ast* sub_ast(struct ast* op1, struct ast* op2);
struct ast* mul_ast(struct ast* op1, struct ast* op2);
struct ast* div_ast(struct ast* op1, struct ast* op2);
struct ast* create_ast_from_number(double d);

