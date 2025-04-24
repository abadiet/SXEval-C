#ifndef SXEVAL_OPERATOR_H
#define SXEVAL_OPERATOR_H

#include "sxeval/error.h"
#include "uthash.h"

struct operator {
    char *name;
    int arityMin, arityMax;
    double (*f)(int, double*);
    UT_hash_handle hh;
};
typedef struct operator operator_t;
typedef operator_t *operators_t;

operators_t sxeval_init_operators(void);
sxeval_error_t sxeval_add_operator(operators_t *ops, const char *name,
    int arityMin, int arityMax, double (*f)(int, double*));
operator_t *sxeval_get_operator(const operators_t ops, const char *name);
void sxeval_free_operators(operators_t *ops);

#endif /* SXEVAL_OPERATOR_H */
