#include "stdafx.h"
#include "ast.h"
#include "context.h"

struct ast_list* new_ast_list()
{
    struct ast_list* al = new struct ast_list;
    return al;
}

struct ast_list* add_ast_to_ast_list(struct ast_list* al, struct ast* a)
{
    assert(al && a);
    al->list.push_back(a);
    return al;
}

struct ast* new_number_ast(double d)
{
    struct ast* a = new struct ast;
    a->type = NODE_NUMBER;
    a->value = d;
    return a;
}

struct ast* new_ref_ast(const char* name)
{
    assert(name);

    struct ast* a = new struct ast;
    memset(a, sizeof(struct ast), 0);
    a->type = NODE_REF;
    a->ref_name = _strdup(name);
    return a;
}

struct ast* new_op2_ast(enum node_type type, struct ast* op1, struct ast* op2)
{
    if (type < NODE_OP2_BEGIN || type >= NODE_OP2_END) {
        assert(false);
        return NULL;
    }

    struct ast* a = new struct ast;
    memset(a, sizeof(struct ast), 0);

    a->type = type;
    a->op2.lchild = op1;
    a->op2.rchild = op2;
    return a;
}

struct ast* new_cond_ast(enum node_type type, struct ast* expr, struct ast_list* stat_list)
{
    if (type < NODE_COND_BEGIN || type >= NODE_COND_END) {
        assert(false);
        return NULL;
    }

    struct ast* a = new struct ast;
    memset(a, sizeof(struct ast), 0);
    a->type = type;
    a->cond.expr = expr;
    a->cond.body = stat_list;
    return a;
}

void eval_ast_list(struct context* ctx, struct ast_list* al)
{
    assert(ctx && al);

    for (unsigned int i = 0; i < al->list.size(); ++i) {
        eval_ast(ctx, al->list[i]);
    }
}

double eval_ast(struct context* ctx, struct ast* a)
{
    if (a->type == NODE_NUMBER)
        return a->value;

    if (a->type == NODE_REF) {
        struct symbol* sym = lookup_symbol(ctx, a->ref_name);
        if (sym == 0 || !sym->isinit) {
            return 0;
        }
        return sym->value;
    }

    // NODE_OP2_xxx
    if (a->type == NODE_OP2_ADD)
        return eval_ast(ctx, a->op2.lchild) + eval_ast(ctx, a->op2.rchild);

    if (a->type == NODE_OP2_SUB)
        return eval_ast(ctx, a->op2.lchild) - eval_ast(ctx, a->op2.rchild);

    if (a->type == NODE_OP2_MUL)
        return eval_ast(ctx, a->op2.lchild) * eval_ast(ctx, a->op2.rchild);

    if (a->type == NODE_OP2_DIV)
        return eval_ast(ctx, a->op2.lchild) / eval_ast(ctx, a->op2.rchild);

    if (a->type == NODE_OP2_G)
        return eval_ast(ctx, a->op2.lchild) > eval_ast(ctx, a->op2.rchild) ? 1 : 0;

    if (a->type == NODE_OP2_GE)
        return eval_ast(ctx, a->op2.lchild) >= eval_ast(ctx, a->op2.rchild) ? 1 : 0;

    if (a->type == NODE_OP2_EQ)
        return eval_ast(ctx, a->op2.lchild) == eval_ast(ctx, a->op2.rchild) ? 1 : 0;

    if (a->type == NODE_OP2_L)
        return eval_ast(ctx, a->op2.lchild) < eval_ast(ctx, a->op2.rchild) ? 1 : 0;

    if (a->type == NODE_OP2_LE)
        return eval_ast(ctx, a->op2.lchild) <= eval_ast(ctx, a->op2.rchild) ? 1 : 0;

    if (a->type == NODE_OP2_ASSIGN) {
        if (a->op2.lchild->type != NODE_REF)
            return 0;

        struct symbol* sym = lookup_symbol(ctx, a->op2.lchild->ref_name);
        sym->isinit = true;
        sym->value = eval_ast(ctx, a->op2.rchild);
        return sym->value;
    }

    // NODE_COND_xxx
    if (a->type == NODE_COND_IF) {
        double istrue = eval_ast(ctx, a->cond.expr);
        if (istrue != 0) {
            eval_ast_list(ctx, a->cond.body);
        }
        
        return 0;
    }

    if (a->type == NODE_COND_WHILE) {
        while (eval_ast(ctx, a->cond.expr) != 0) {
            eval_ast_list(ctx, a->cond.body);
        }
        return 0;
    }

    assert(false);
    return 0;
}

void print_ast(struct context* ctx, struct ast* a)
{
    if (a->type == NODE_NUMBER) {
        printf("%lf\n>", a->value);
        return;
    }

    if (a->type == NODE_REF) {
        struct symbol* sym = lookup_symbol(ctx, a->ref_name);
        if (sym->isinit == false) {
            printf("error: symbol %s not initialized. default 0\n>", a->ref_name);
        }
        else {
            printf("%lf\n>", sym->value);
        }
        return;
    }

    if (a->type >= NODE_OP2_BEGIN && a->type < NODE_OP2_END) {
        double v = eval_ast(ctx, a);
        printf("%lf\n>", v);
        return;
    }

    if (a->type >= NODE_COND_BEGIN && a->type < NODE_COND_END) {
        eval_ast(ctx, a);
        printf("eval condition.\n>");
        return;
    }

    assert(false);
}
