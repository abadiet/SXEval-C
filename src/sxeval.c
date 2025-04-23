#include "sxeval.h"

sxeval_error_t sxeval_evaluate(sexp_t *exp, const operators_t ops,
    const context_t ctx, double *result)
{
    variable_t *var;
    operator_t *op;
    double *args;
    sexp_t *elem;
    int nargs, i;
    sxeval_error_t res;

    if (!exp) {
        return SXEVAL_INVALID_EXPRESSION;
    }
    if (!ops) {
        return SXEVAL_INVALID_OPERATORS;
    }
    if (!ctx) {
        return SXEVAL_INVALID_CONTEXT;
    }

    switch (exp->ty) {
        case SEXP_VALUE:
            if (exp->aty != SEXP_BINARY) {
                if (sscanf(exp->val, "%lf", result) != 1) {
                    /* as this is not castable to a double, this is likely
                        a variable */
                    var = sxeval_get_variable(ctx, exp->val);
                    if (var) {
                        *result = var->value;
                    } else {
                        return SXEVAL_UNDEFINED_VARIABLE;
                    }
                }
            } else {
                return SXEVAL_BINARY_NOT_SUPPORTED;
            }
            break;

        case SEXP_LIST:
            op = sxeval_get_operator(ops, exp->list->val);
            if (!op) {
                return SXEVAL_UNDEFINED_OPERATOR;
            }

            nargs = 0;
            elem = exp->list->next;
            while (elem) {
                nargs++;
                elem = elem->next;
            }
            if (nargs < op->arityMin || (nargs > op->arityMax
                && op->arityMax >= 0))
            {
                return SXEVAL_INVALID_USE_OF_OPERATOR;
            }

            args = (double *) malloc(nargs * sizeof(double));
            if (!args) {
                return SXEVAL_OUT_OF_MEMORY;
            }
            elem = exp->list->next;
            for (i = 0; i < nargs; i++) {
                res = sxeval_evaluate(elem, ops, ctx, args + i);
                if (res != SXEVAL_NO_ERROR) {
                    return res;
                }
                elem = elem->next;
            }

            *result = op->f(nargs, args);

            free(args);
            break;
    }

    return SXEVAL_NO_ERROR;
}
