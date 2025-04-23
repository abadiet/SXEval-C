#include "sexp.h"
#include "sxeval.h"
#include "context.h"
#include "operator.h"
#include "error.h"
#include <stdio.h>

double add(int argc, double *args) {
    double sum = 0;
    for (int i = 0; i < argc; i++) {
        sum += args[i];
    }
    return sum;
}

int main(int argc, char *argv[]) {
    sexp_t* exp;
    context_t ctx;
    operators_t ops;
    sxeval_error_t res;
    double result;

    if (argc < 2) {
        printf("Usage: %s '<s-expression>'\n", argv[0]);
        return 1;
    }

    exp = parse_sexp(argv[1], strlen(argv[1]));

    ops = sxeval_init_operators();
    res = sxeval_add_operator(&ops, "+", 2, SXEVAL_NO_LIMIT, add);
    if (res != SXEVAL_NO_ERROR) {
        fprintf(stderr, "Error adding operator: %s\n",
            sxeval_error_to_string(res));
        destroy_sexp(exp);
        sxeval_free_operators(&ops);
        return 1;
    }

    ctx = sxeval_init_context();
    res = sxeval_add_variable(&ctx, "x", 10.0);
    if (res != SXEVAL_NO_ERROR) {
        fprintf(stderr, "Error adding variable: %s\n",
            sxeval_error_to_string(res));
        destroy_sexp(exp);
        sxeval_free_operators(&ops);
        sxeval_free_context(&ctx);
        return 1;
    }

    res = sxeval_evaluate(exp, ops, ctx, &result);
    if (res != SXEVAL_NO_ERROR) {
        fprintf(stderr, "Error evaluating expression: %s\n",
            sxeval_error_to_string(res));
        destroy_sexp(exp);
        sxeval_free_operators(&ops);
        sxeval_free_context(&ctx);
        return 1;
    }

    printf("Result: %lf\n", result);

    destroy_sexp(exp);
    sexp_cleanup();
    sxeval_free_operators(&ops);
    sxeval_free_context(&ctx);
    return 0;
}
