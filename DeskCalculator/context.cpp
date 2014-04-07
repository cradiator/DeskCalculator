#include "stdafx.h"
#include "context.h"

struct symbol* lookup_symbol(struct context* current_ctx, char* name)
{
    assert(current_ctx && name);
    
    struct context* ctx = current_ctx;
    struct symbol* sym = 0;

    // find existing symbol.
    while (ctx && !sym) {
        for (unsigned int i = 0; i < ctx->symbol_list.size(); ++i) {
            if (strcmp(ctx->symbol_list[i].name.c_str(), name) == 0) {
                sym = &ctx->symbol_list[i];
                break;
            }
        }

        ctx = ctx->prev;
    }

    // no existing, create an uninit one.
    if (!sym) {
        struct symbol s;
        s.isinit = false;
        s.name   = name;
        s.value  = 0;

        // add it to top level context
        current_ctx->symbol_list.push_back(s);

        sym = &current_ctx->symbol_list[current_ctx->symbol_list.size() - 1];
    }

    return sym;
}

struct context* new_context(struct context* prev_ctx)
{
    struct context* ctx = new struct context;
    ctx->prev = prev_ctx;
    return ctx;
}

void destroy_context(struct context* ctx)
{
    delete ctx;
}

struct context* get_global_context()
{
    static struct context* ctx = 0;
    if (ctx)
        return ctx;

    ctx = new_context(0);
    return ctx;
}
