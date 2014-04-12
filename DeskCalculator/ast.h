#pragma once

#include "context.h"
#include <string>

enum node_type {
    NODE_NUMBER = 0,
    NODE_REF,   // reference a symbol

    NODE_OP2_BEGIN = 1000,
    NODE_OP2_ADD = NODE_OP2_BEGIN,
    NODE_OP2_SUB,
    NODE_OP2_MUL,
    NODE_OP2_DIV,
    NODE_OP2_G,
    NODE_OP2_GE,
    NODE_OP2_EQ,
    NODE_OP2_L,
    NODE_OP2_LE,
    NODE_OP2_ASSIGN,
    NODE_OP2_END,

    NODE_COND_BEGIN = 2000,
    NODE_COND_IF = NODE_COND_BEGIN,
    NODE_COND_WHILE,
    NODE_COND_END,

};

struct ast_list {
    std::vector<struct ast*> list;
};

struct ast {
    enum node_type type;
    union {
        // NODE_NUMBER
        double value;

        // NODE_REF
        char* ref_name;

        // for NODE_OP2_xxx
        struct {
            struct ast* lchild;
            struct ast* rchild;
        } op2;

        // for NODE_COND_xxx
        struct {
            struct ast* expr;
            struct ast_list* body;
        } cond;
    };
};

#ifdef __cplusplus
extern "C" {
#endif

    struct ast_list* new_ast_list();
    struct ast_list* add_ast_to_ast_list(struct ast_list* al, struct ast* a);

    double eval_ast(struct context* ctx, struct ast* a);

    // NODE_NUMBER
    struct ast* new_number_ast(double d);

    // NODE_REF
    struct ast* new_ref_ast(const char* name);

    // NODE_OP2_xxx
    struct ast* new_op2_ast(enum node_type type, struct ast* op1, struct ast* op2);

    // NODE_COND_xxx
    struct ast* new_cond_ast(enum node_type type, struct ast* expr, struct ast_list* stat_list);

    void print_ast(struct context* ctx, struct ast* a);

#ifdef __cplusplus
}
#endif
