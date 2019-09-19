#include "headers.h"

/* definition and initialization of parser type */

mpc_parser_t *Number;
mpc_parser_t *Symbol;
mpc_parser_t *String;
mpc_parser_t *SExpr;
mpc_parser_t *QExpr;
mpc_parser_t *Expr;
mpc_parser_t *Lisp;

void parser_initialize() {
    Number = mpc_new("number");
    Symbol = mpc_new("symbol");
    String = mpc_new("string");
    SExpr = mpc_new("sexpr");
    QExpr = mpc_new("qexpr");
    Expr = mpc_new("expr");
    Lisp = mpc_new("lisp");
}

int main() {
    puts("Lisp ver 0.0.1\n");
    puts("Type \"$exit\" to exit.\n");

    parser_initialize();

    /* define lisp grammar */

    mpca_lang(MPCA_LANG_DEFAULT,
              "number : /-?[0-9]+/ ;"
              "symbol :/[a-zA-Z0-9_+\\-*\\/\\\\=<>!&]+/;"
              "string  : /\"(\\\\.|[^\"])*\"/ ;"
              "sexpr  : '(' <expr>* ')' ;"
              "qexpr  : ''' <expr> ;"
              "expr   : <number> | <symbol> | <sexpr> | <qexpr> | <string> ;"
              "lisp  : /^/ <expr>* /$/ ;",
              Number, Symbol, String, SExpr, QExpr, Expr, Lisp);

    mpc_result_t r;

    while (1) {
        char *input = readline("LISP> ");
        add_history(input);
        if (strcmp(input, "$exit") == 0) {
            break;
        }
        if (mpc_parse("<stdin>", input, Lisp, &r)) {
            //mpc_ast_print(r.output);

            lval **cur = NULL;
            int num = 0;
            cur = lval_read(r.output, &num);
            lval_print(num, cur);

            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
        free(input);
    }

    mpc_cleanup(6, Number, Symbol, String, SExpr, QExpr, Lisp);
    return 0;
}