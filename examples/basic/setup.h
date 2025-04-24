#ifndef SXEVAL_EXAMPLES_BASIC_SETUP_H
#define SXEVAL_EXAMPLES_BASIC_SETUP_H

#include "sexp.h"
#include "cstring.h"
#include "sxeval.h"
#include "context.h"
#include "operator.h"
#include "error.h"
#include <stdio.h>

#define FREE()                                                                 \
    destroy_sexp(exp);                                                         \
    sxeval_free(&sxeval);                                                      \
    sxeval_free_operators(&ops);                                               \
    sxeval_free_context(&ctx);                                                 \
    sexp_cleanup();

#define ADD_OP(name, arityMin, arityMax, f)                                    \
    res = sxeval_add_operator(&ops, name, arityMin, arityMax, f);              \
    if (res != SXEVAL_NO_ERROR) {                                              \
        fprintf(stderr, "Error adding operator: %s\n",                         \
            sxeval_error_to_string(res));                                      \
        FREE()                                                                 \
        return 1;                                                              \
    }

#define ADD_VAR(name, value)                                                   \
    res = sxeval_add_variable(&ctx, name, value);                              \
    if (res != SXEVAL_NO_ERROR) {                                              \
        fprintf(stderr, "Error adding variable: %s\n",                         \
            sxeval_error_to_string(res));                                      \
        FREE()                                                                 \
        return 1;                                                              \
    }

void print_exp(sexp_t *exp);

void print_exp(sexp_t *exp) {
    CSTRING *parsed;
    parsed = snew(BUFSIZ);
    print_sexp_cstr(&parsed, exp, BUFSIZ);
    printf("Parsed expression: %s\n", toCharPtr(parsed));
    sdestroy(parsed);
}

#endif /* SXEVAL_EXAMPLES_BASIC_SETUP_H */
