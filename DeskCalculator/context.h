#pragma once

#include <string>
#include <vector>

struct symbol {
    bool isinit;
    std::string name;
    double value;
};

struct context {
    struct context* prev;
    std::vector<struct symbol> symbol_list;
};

// get the symbol pointer from context.
// if not exist, create a new uninitialized symbol.
struct symbol* lookup_symbol(struct context* current_ctx, const char* name);

// create a new context
struct context* new_context(struct context* prev_ctx);

// destroy a context
void destroy_context(struct context* ctx);

struct context* get_global_context();
