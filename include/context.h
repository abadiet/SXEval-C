#ifndef SXEVAL_CONTEXT_H
#define SXEVAL_CONTEXT_H

#include "error.h"
#include "uthash.h"

struct variable {
    char *name;
    double value;
    UT_hash_handle hh;
};
typedef struct variable variable_t;
typedef variable_t *context_t;

context_t sxeval_init_context(void);
sxeval_error_t sxeval_add_variable(context_t *ctx, const char *name,
    double value);
variable_t *sxeval_get_variable(const context_t ctx, const char *name);
void sxeval_free_context(context_t *ctx);

#endif /* SXEVAL_CONTEXT_H */
