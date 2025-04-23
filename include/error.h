#ifndef SXEVAL_ERROR_H
#define SXEVAL_ERROR_H

enum sxeval_error {
    SXEVAL_NO_ERROR = 0,
    SXEVAL_INVALID_EXPRESSION,
    SXEVAL_INVALID_OPERATORS,
    SXEVAL_INVALID_CONTEXT,
    SXEVAL_UNDEFINED_VARIABLE,
    SXEVAL_UNDEFINED_OPERATOR,
    SXEVAL_BINARY_NOT_SUPPORTED,
    SXEVAL_OUT_OF_MEMORY,
    SXEVAL_INVALID_USE_OF_OPERATOR
};
typedef enum sxeval_error sxeval_error_t;

const char *sxeval_error_to_string(sxeval_error_t error);

#endif /* SXEVAL_ERROR_H */
