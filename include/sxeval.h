#ifndef SXEVAL_SXEVAL_H
#define SXEVAL_SXEVAL_H

#include "operator.h"
#include "context.h"
#include "sexp.h"
#include "error.h"
#include <stdbool.h>

#define SXEVAL_NO_LIMIT -1

struct operation;
typedef struct operation *sxeval_t;

sxeval_t sxeval_init(void);
sxeval_error_t sxeval_build(sxeval_t *sxeval, sexp_t *exp,
    const operators_t ops, const context_t ctx);
double sxeval_evaluate(sxeval_t sxeval);
void sxeval_free(sxeval_t *sxeval);

#endif /* SXEVAL_SXEVAL_H */
