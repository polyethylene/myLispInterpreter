#include <stdio.h>
#include "mpc.h"

#ifdef _WIN32

#include <string.h>

static char buffer[2048];

char *readline(char *prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char *cpy = malloc(strlen(buffer) + 1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy) - 1] = '\0';
    return cpy;
}

void add_history(char *unused) {}

#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

/* definition of parser type */

mpc_parser_t *Number;
mpc_parser_t *Symbol;
mpc_parser_t *String;
mpc_parser_t *S_Exp;
mpc_parser_t *Q_Exp;
mpc_parser_t *Lisp;

int main() {
    puts("Lisp ver 0.0.1\n");
    puts("Press esc to exit.\n");

    mpc_result_t r;

    while (1) {
        char *input = readline("LISP> ");
        add_history(input);

        mpca_lang(MPCA_LANG_DEFAULT,
                ""
                ""
                "",
                )

        if (mpc_parse("<stdin>", input, xxx, &r)) {
            mpc_ast_print(r.output);
            //lval *x = lval_read(r.output);

            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }
    return 0;
}