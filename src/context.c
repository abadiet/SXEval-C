#include "context.h"

context_t sxeval_init_context(void) {
    return NULL;
}

sxeval_error_t sxeval_add_variable(context_t *ctx, const char *name,
    double value)
{
    variable_t *var = (variable_t *) malloc(sizeof(variable_t));
    if (!var) {
        return SXEVAL_OUT_OF_MEMORY;
    }
    var->name = strdup(name);
    var->value = value;
    HASH_ADD_STR(*ctx, name, var);
    return SXEVAL_NO_ERROR;
}

variable_t *sxeval_get_variable(const context_t ctx, const char *name) {
    variable_t *var;
    HASH_FIND_STR(ctx, name, var);
    return var;
}

void sxeval_free_context(context_t *ctx) {
    variable_t *var, *tmp;
    if (!ctx || !*ctx) {
        return;
    }
    HASH_ITER(hh, *ctx, var, tmp) {
        HASH_DEL(*ctx, var);
        free(var->name);
        free(var);
    }
    *ctx = NULL;
}
