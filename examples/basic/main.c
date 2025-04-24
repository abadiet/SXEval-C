#include "setup.h"
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

double mult(int argc, double *args) {
    double m = 1;
    for (int i = 0; i < argc; i++) {
        m *= args[i];
    }
    return m;
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
    ctx = sxeval_init_context();

    ADD_OP("+", 2, SXEVAL_NO_LIMIT, add)
    ADD_OP("*", 2, SXEVAL_NO_LIMIT, mult)

    ADD_VAR("x", 5.0)

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

    FREE()
    return 0;
}
