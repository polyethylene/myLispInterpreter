#include "mpc.h"
#include "value_type.h"
#include "read.h"
#include <string.h>

lval *lval_read_number(mpc_ast_t *v) {
    errno = 0;
    int x = strtol(v->contents, NULL, 10);
    if (errno == ERANGE) {
        return lval_err("invalid number");
    } else {
        return lval_num(x);
    }
}

lval *lval_read_string(mpc_ast_t *v) {
    return lval_str(v->contents);
}

lval *lval_read_single(mpc_ast_t *v) {
    if (strstr(v->tag, "number")) { return lval_read_number(v); }
    if (strstr(v->tag, "symbol")) { return lval_sym(v->contents); }
    if (strstr(v->tag, "string")) { return lval_read_string(v); }

    lval *x = NULL;
    if (strstr(v->tag, "qexpr")) {
        x = lval_qexpr();
        x->tar = lval_read_single(v->children[1]);
        return x;
    }
    if (strstr(v->tag, "sexpr")) { x = lval_sexpr(); }

    for (int i = 0; i < v->children_num; i++) {
        if (strcmp(v->children[i]->contents, "(") == 0) { continue; }
        if (strcmp(v->children[i]->contents, ")") == 0) { continue; }
        if (strcmp(v->children[i]->contents, "'") == 0) { continue; }
        if (strcmp(v->children[i]->contents, "\"") == 0) { continue; }
        x = lval_add(x, lval_read_single(v->children[i]));
    }
    return x;
}

// read multiple expression, r must be a null pointer (in order
lval **lval_read(mpc_ast_t *v, int *num_p) {
    // if it is the root of the tree
    lval **r = NULL;
    if (strcmp(v->tag, ">") == 0) {
        // if not empty (except for ^ and $), to avoid malloc(0)
        if (v->children_num > 2) {
            r = malloc(sizeof(lval *) * (v->children_num - 2));
            for (int i = 1; i < v->children_num - 1; i++) {
                r[i - 1] = lval_read_single(v->children[i]);
            }
        }
        printf("\n");
        *num_p = v->children_num - 2;
    } else {
        r = malloc(sizeof(lval *));
        *r = lval_read_single(v);
        *num_p = 1;
    }
    return r;
}

void lval_print_single(lval *v) {
    switch (v->type) {
        case LTYPE_NUM:
            printf("%d", v->num);
            break;
        case LTYPE_SYM:
            printf("%s", v->sym);
            break;
        case LTYPE_ERR:
            printf("Error: %s", v->err);
            break;
        case LTYPE_SEXPR:
            printf("(");
            for (int i = 0; i < v->count; i++) {
                lval_print_single(v->elem[i]);
                if (i != (v->count - 1)) {
                    putchar(' ');
                }
            }   // print all element in it
            printf(")");
            break;
        case LTYPE_QEXPR:
            printf("'");
            lval_print_single(v->tar); // just print a "'" before its target
            break;
        default:
            break;
    }
}

void lval_print(int n, lval **v) {
    for (int i = 0; i < n; i++) {
        lval_print_single(v[i]);
        putchar('\n');
    }
}
