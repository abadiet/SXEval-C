#ifndef SXEVAL_SXEVAL_H
#define SXEVAL_SXEVAL_H

#include "operator.h"
#include "context.h"
#include "sexp.h"
#include "error.h"

#define SXEVAL_NO_LIMIT -1

sxeval_error_t sxeval_evaluate(sexp_t *exp, const operators_t ops,
    const context_t ctx, double *result);

#endif /* SXEVAL_SXEVAL_H */
