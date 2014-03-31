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

