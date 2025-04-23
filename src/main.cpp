#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include <cmath>
#include "sexp.h"

using Context = std::unordered_map<std::string, double>;

enum Operator {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    MODULO,
    POWER,
    GREATER,
    LESS,
    GREATER_EQUAL,
    LESS_EQUAL,
    EQUAL,
    NOT_EQUAL,
    AND,
    OR,
    NOT,
    NAND,
    NOR,
    XOR,
    XNOR,
    ABS,
    SQRT,
    EXP,
    LOG,
    LOG2,
    LOG10,
    LOGN,
    SIN,
    COS,
    TAN,
    ASIN,
    ACOS,
    ATAN,
    ATAN2,
    SINH,
    COSH,
    TANH,
    ASINH,
    ACOSH,
    ATANH,
    CEIL,
    FLOOR,
    ROUND,
    MAX,
    MIN,
    DEG2RAD,
    RAD2DEG,
    PI,
    E
};

const std::unordered_map<std::string, Operator> operators_map = {
    {"+", ADD},
    {"-", SUBTRACT},
    {"*", MULTIPLY},
    {"/", DIVIDE},
    {"%", MODULO},
    {"^", POWER},
    {">", GREATER},
    {"<", LESS},
    {">=", GREATER_EQUAL},
    {"<=", LESS_EQUAL},
    {"==", EQUAL},
    {"!=", NOT_EQUAL},
    {"and", AND},
    {"or", OR},
    {"not", NOT},
    {"nand", NAND},
    {"nor", NOR},
    {"xor", XOR},
    {"xnor", XNOR},
    {"abs", ABS},
    {"sqrt", SQRT},
    {"exp", EXP},
    {"log", LOG},
    {"log2", LOG2},
    {"log10", LOG10},
    {"logn", LOGN},
    {"sin", SIN},
    {"cos", COS},
    {"tan", TAN},
    {"asin", ASIN},
    {"acos", ACOS},
    {"atan", ATAN},
    {"atan2", ATAN2},
    {"sinh", SINH},
    {"cosh", COSH},
    {"tanh", TANH},
    {"asinh", ASINH},
    {"acosh", ACOSH},
    {"atanh", ATANH},
    {"ceil", CEIL},
    {"floor", FLOOR},
    {"round", ROUND},
    {"max", MAX},
    {"min", MIN},
};

double evaluate(sexp_t* exp, const Context& ctx) {
    if (!exp) throw std::runtime_error("Null expression");

    switch (exp->ty) {
        case SEXP_VALUE:
            if (exp->aty != SEXP_BINARY) {
                const char *val = exp->val;
                try {
                    return std::stod(val);
                } catch (...) {
                    const auto it = ctx.find(val);
                    if (it != ctx.end()) {
                        return it->second;
                    } else {
                        const std::string s(val);
                        throw std::runtime_error("Unknown variable: " + s);
                    }
                }
            } else {
                throw std::runtime_error("Binary is not supported");
            }
            break;
        
        case SEXP_LIST:
            {
                sexp_t* larg = exp->list->next;
                if (larg == nullptr) {
                    throw std::runtime_error("Operators need at least one argument");
                }
                sexp_t* rarg = larg->next;
                const double l = evaluate(larg, ctx);
                const double r = rarg ? evaluate(rarg, ctx) : 0.0;
                switch (operators_map.at(exp->list->val)) {
                    case ADD:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator + needs two arguments");
                        }
                        return l + r;
                        break;
                    case SUBTRACT:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator - needs two arguments");
                        }
                        return l - r;
                        break;
                    case MULTIPLY:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator * needs two arguments");
                        }
                        return l * r;
                        break;
                    case DIVIDE:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator / needs two arguments");
                        }
                        return l / r;
                        break;
                    case MODULO:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator % needs two arguments");
                        }
                        return static_cast<int>(l) % static_cast<int>(r);
                        break;
                    case POWER:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator ^ needs two arguments");
                        }
                        return std::pow(l, r);
                        break;
                    case GREATER:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator > needs two arguments");
                        }
                        return l > r;
                        break;
                    case LESS:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator < needs two arguments");
                        }
                        return l < r;
                        break;
                    case GREATER_EQUAL:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator >= needs two arguments");
                        }
                        return l >= r;
                        break;
                    case LESS_EQUAL:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator <= needs two arguments");
                        }
                        return l <= r;
                        break;
                    case EQUAL:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator == needs two arguments");
                        }
                        return l == r;
                        break;
                    case NOT_EQUAL:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator != needs two arguments");
                        }
                        return l != r;
                        break;
                    case AND:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator and needs two arguments");
                        }
                        return l && r;
                        break;
                    case OR:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator or needs two arguments");
                        }
                        return l || r;
                        break;
                    case NOT:
                        return !l;
                        break;
                    case NAND:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator nand needs two arguments");
                        }
                        return !(l && r);
                        break;
                    case NOR:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator nor needs two arguments");
                        }
                        return !(l || r);
                        break;
                    case XOR:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator xor needs two arguments");
                        }
                        return (l && !r) || (!l && r);
                        break;
                    case XNOR:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator xnor needs two arguments");
                        }
                        return !(l && !r) && (!l && r);
                        break;
                    case ABS:
                        return std::abs(l);
                        break;
                    case SQRT:
                        return std::sqrt(l);
                        break;
                    case EXP:
                        return std::exp(l);
                        break;
                    case LOG:
                        return std::log(l);
                        break;
                    case LOG2:
                        return std::log2(l);
                        break;
                    case LOG10:
                        return std::log10(l);
                        break;
                    case LOGN:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator logn needs two arguments");
                        }
                        return std::log(l) / std::log(r);
                        break;
                    case SIN:
                        return std::sin(l);
                        break;
                    case COS:
                        return std::cos(l);
                        break;
                    case TAN:
                        return std::tan(l);
                        break;
                    case ASIN:
                        return std::asin(l);
                        break;
                    case ACOS:
                        return std::acos(l);
                        break;
                    case ATAN:
                        return std::atan(l);
                        break;
                    case ATAN2:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator atan2 needs two arguments");
                        }
                        return std::atan2(l, r);
                        break;
                    case SINH:
                        return std::sinh(l);
                        break;
                    case COSH:
                        return std::cosh(l);
                        break;
                    case TANH:
                        return std::tanh(l);
                        break;
                    case ASINH:
                        return std::asinh(l);
                        break;
                    case ACOSH:
                        return std::acosh(l);
                        break;
                    case ATANH:
                        return std::atanh(l);
                        break;
                    case CEIL:
                        return std::ceil(l);
                        break;
                    case FLOOR:
                        return std::floor(l);
                        break;
                    case ROUND:
                        return std::round(l);
                        break;
                    case MAX:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator max needs two arguments");
                        }
                        return std::max(l, r);
                        break;
                    case MIN:
                        if (rarg == nullptr) {
                            throw std::runtime_error("Operator min needs two arguments");
                        }
                        return std::min(l, r);
                        break;
                    case DEG2RAD:
                        return l * M_PI / 180.0;
                        break;
                    case RAD2DEG:
                        return l * 180.0 / M_PI;
                        break;
                    case PI:
                        return M_PI;
                        break;
                    case E:
                        return M_E;
                        break;
                }
            }
        default:
            throw std::runtime_error("Unsupported expression type");
            break;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " '<s-expression>'\n";
        return 1;
    }

    sexp_t* sexpr = parse_sexp(argv[1], strlen(argv[1]));

    const Context ctx = {{"x", 4}};

    try {
        double result = evaluate(sexpr, ctx);
        std::cout << "Result: " << result << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error evaluating expression: " << e.what() << "\n";
    }

    destroy_sexp(sexpr);
    sexp_cleanup();

    return 0;
}
