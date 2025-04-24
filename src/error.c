#include "error.h"

const char *sxeval_error_to_string(sxeval_error_t error) {
    switch (error) {
        case SXEVAL_NO_ERROR:
            return "No error";
        case SXEVAL_INVALID_EXPRESSION:
            return "Invalid expression";
        case SXEVAL_INVALID_OPERATORS:
            return "Invalid operators";
        case SXEVAL_INVALID_CONTEXT:
            return "Invalid context";
        case SXEVAL_UNDEFINED_VARIABLE:
            return "Undefined variable";
        case SXEVAL_UNDEFINED_OPERATOR:
            return "Undefined operator";
        case SXEVAL_BINARY_NOT_SUPPORTED:
            return "Binary not supported";
        case SXEVAL_OUT_OF_MEMORY:
            return "Out of memory";
        case SXEVAL_INVALID_USE_OF_OPERATOR:
            return "Invalid use of operator";
        default:
            return "Unknown error";
    }
}
