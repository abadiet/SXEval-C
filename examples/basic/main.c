#include "setup.h"
#include "sexp.h"
#include "sxeval.h"
#include "context.h"
#include "operator.h"
#include "error.h"
#include <stdio.h>

double add(int n, double *args);
double mult(int n, double *args);

int main(int argc, char *argv[]) {
    sexp_t* exp;
    sxeval_t sxeval;
    context_t ctx;
    operators_t ops;
    sxeval_error_t res;
    double result;

    if (argc < 2) {
        printf("Usage: %s '<s-expression>'\n", argv[0]);
        return 1;
    }

    exp = parse_sexp(argv[1], strlen(argv[1]));
    sxeval = sxeval_init();
    ops = sxeval_init_operators();
    ctx = sxeval_init_context();

    print_exp(exp);

    ADD_OP("+", 2, SXEVAL_NO_LIMIT, add)
    ADD_OP("*", 2, SXEVAL_NO_LIMIT, mult)

    ADD_VAR("x", 5.0)

    res = sxeval_build(&sxeval, exp, ops, ctx);
    if (res != SXEVAL_NO_ERROR) {
        fprintf(stderr, "Error building sxeval: %s\n",
            sxeval_error_to_string(res));
        FREE()
        return 1;
    }

    result = sxeval_evaluate(sxeval);
    printf("Result: %lf\n", result);

    FREE()
    return 0;
}

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
