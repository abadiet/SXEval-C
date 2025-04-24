#include "sxeval/operator.h"

operators_t sxeval_init_operators(void) {
    return NULL;
}

sxeval_error_t sxeval_add_operator(operators_t *ops, const char *name,
    int arityMin, int arityMax, double (*f)(int, double*))
{
    operator_t *op = (operator_t *) malloc(sizeof(operator_t));
    if (!op) {
        return SXEVAL_OUT_OF_MEMORY;
    }
    op->name = strdup(name);
    op->arityMin = arityMin;
    op->arityMax = arityMax;
    op->f = f;
    HASH_ADD_KEYPTR(hh, *ops, op->name, strlen(op->name), op);
    return SXEVAL_NO_ERROR;
}

operator_t *sxeval_get_operator(const operators_t ops, const char *name) {
    operator_t *op;
    HASH_FIND_STR(ops, name, op);
    return op;
}

void sxeval_free_operators(operators_t *ops) {
    operator_t *op, *tmp;
    if (!ops || !*ops) {
        return;
    }
    HASH_ITER(hh, *ops, op, tmp) {
        HASH_DEL(*ops, op);
        free(op->name);
        free(op);
    }
    *ops = NULL;
}
