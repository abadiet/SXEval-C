#include "sxeval/sxeval.h"

#ifdef SXEVAL_DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

struct argument {
    bool is_variable;
    union {
        double val;
        double *var;
    };
};

struct operation {
    operator_t *op;
    struct argument *args;
    int nargs;
    double result;
    struct operation *next;
};

sxeval_error_t _sxeval_build(sxeval_t *sxeval, sexp_t *exp,
    const operators_t ops, const context_t ctx, struct argument *arg);

sxeval_t sxeval_init(void) {
    return NULL;
}

sxeval_error_t sxeval_build(sxeval_t *sxeval, sexp_t *exp,
    const operators_t ops, const context_t ctx)
{
    sxeval_error_t res;
    struct argument *arg;

    arg = (struct argument *) malloc(sizeof(struct argument));
    if (!arg) {
        return SXEVAL_OUT_OF_MEMORY;
    }
    res = _sxeval_build(sxeval, exp, ops, ctx, arg);
    free(arg);

    return res;
}

double sxeval_evaluate(sxeval_t sxeval) {
    double *args;
    int i;

    args = (double *) malloc((unsigned long) sxeval->nargs *
        sizeof(double));
    for (i = 0; i < sxeval->nargs; i++) {
        if (sxeval->args[i].is_variable) {
            args[i] = *(sxeval->args[i].var);
        } else {
            args[i] = sxeval->args[i].val;
        }
    }

    sxeval->result = sxeval->op->f(sxeval->nargs, args);

    free(args);
    if (!sxeval->next) {
        return sxeval->result;
    }
    return sxeval_evaluate(sxeval->next);
}

void sxeval_free(sxeval_t *sxeval) {
    sxeval_t next;

    if (!sxeval || !*sxeval) {
        return;
    }

    next = (*sxeval)->next;
    free((*sxeval)->args);
    free(*sxeval);
    *sxeval = next;
    sxeval_free(sxeval);

}

sxeval_error_t _sxeval_build(sxeval_t *sxeval, sexp_t *exp,
    const operators_t ops, const context_t ctx, struct argument *arg)
{
    sexp_t *elem;
    int i;
    sxeval_error_t res;
    sxeval_t new;
    variable_t *var;

    if (!exp) {
        return SXEVAL_INVALID_EXPRESSION;
    }
    if (!ops) {
        return SXEVAL_INVALID_OPERATORS;
    }
    if (!ctx) {
        return SXEVAL_INVALID_CONTEXT;
    }

    DEBUG_PRINT("%p exp: %s\n", (void*) *sxeval, exp->val);

    switch (exp->ty) {
        case SEXP_VALUE:
            if (!arg) {
                return SXEVAL_INVALID_EXPRESSION;
            }

            if (exp->aty != SEXP_BINARY) {
                if (sscanf(exp->val, "%lf", &arg->val) != 1) {
                    /* as this is not castable to a double, this is likely
                        a variable */
                    var = sxeval_get_variable(ctx, exp->val);
                    if (var) {
                        arg->var = &var->value;
                        arg->is_variable = true;
                        DEBUG_PRINT("%p    found variable %s = %lf @%p\n",
                            (void*) *sxeval, var->name, *arg->var,
                            (void*) arg->var);
                    } else {
                        return SXEVAL_UNDEFINED_VARIABLE;
                    }
                } else {
                    arg->is_variable = false;
                    DEBUG_PRINT("%p    found value %f\n", (void*) *sxeval,
                        arg->val);
                }
            } else {
                return SXEVAL_BINARY_NOT_SUPPORTED;
            }
            break;

        case SEXP_LIST:
            new = (sxeval_t) malloc(sizeof(struct operation));
            if (!new) {
                return SXEVAL_OUT_OF_MEMORY;
            }
            new->next = *sxeval;
            arg->is_variable = true;
            arg->var = &new->result;
            *sxeval = new;

            DEBUG_PRINT("%p    found list\n", (void*) new);

            new->op = sxeval_get_operator(ops, exp->list->val);
            if (!new->op) {
                return SXEVAL_UNDEFINED_OPERATOR;
            }

            DEBUG_PRINT("%p    found operator %s\n", (void*) new,
                new->op->name);

            new->nargs = 0;
            new->args = NULL;
            elem = exp->list->next;
            while (elem) {
                new->nargs++;
                elem = elem->next;
            }
            if (new->nargs < new->op->arityMin || (new->nargs
                > new->op->arityMax && new->op->arityMax >= 0))
            {
                return SXEVAL_INVALID_USE_OF_OPERATOR;
            }

            DEBUG_PRINT("%p    found %d args\n", (void*) new,
                new->nargs);

            new->args = (struct argument *) malloc(
                (unsigned long) new->nargs *
                sizeof(struct argument));
            if (!new->args) {
                return SXEVAL_OUT_OF_MEMORY;
            }
            elem = exp->list->next;
            for (i = 0; i < new->nargs; i++) {
                res = _sxeval_build(sxeval, elem, ops, ctx,
                    new->args + i);
                if (res != SXEVAL_NO_ERROR) {
                    return res;
                }
                DEBUG_PRINT("%p        arg %d: %f @%p\n", (void*) new, i,
                    new->args[i].val, new->args[i].is_variable ?
                    (void*) new->args[i].var : NULL);
                elem = elem->next;
            }

            break;
    }

    return SXEVAL_NO_ERROR;
}
