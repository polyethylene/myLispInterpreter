#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "value_type.h"

lval *lval_num(int n) {
    lval *r = malloc(sizeof(lval));
    r->type = LTYPE_NUM;
    r->num = n;
    return r;
}

lval *lval_sym(char *s) {
    lval *r = malloc(sizeof(lval));
    r->type = LTYPE_SYM;
    r->sym = malloc(strlen(s) + 1);
    strcpy(r->sym, s);
    return r;
}

lval *lval_err(char *s) {
    lval *r = malloc(sizeof(lval));
    r->type = LTYPE_ERR;
    r->err = malloc(strlen(s) + 1);
    strcpy(r->err, s);
    return r;
}

lval *lval_str(char *s) {
    lval *r = malloc(sizeof(lval));
    r->type = LTYPE_STR;
    r->sym = malloc(strlen(s) + 1);
    strcpy(r->sym, s);
    return r;
}

lval *lval_sexpr() {
    lval *r = malloc(sizeof(lval));
    r->type = LTYPE_SEXPR;
    r->count = 0;
    r->elem = NULL;
    return r;
}

lval *lval_qexpr() {
    lval *r = malloc(sizeof(lval));
    r->type = LTYPE_QEXPR;
    r->tar = NULL;
    return r;
}

void lval_del(lval *a) {
    if (!a) {
        return;
    }
    switch (a->type) {
        case LTYPE_NUM:
            break;
        case LTYPE_SYM:
            free(a->sym);
            break;
        case LTYPE_ERR:
            free(a->err);
            break;
        case LTYPE_STR:
            free(a->str);
            break;
        case LTYPE_SEXPR:
            for (int i = 0; i < a->count; i++) {
                lval_del(a->elem[i]);
            }
            break;
        case LTYPE_QEXPR:
            free(a->tar);
            break;
        default:
            break;
    }
    free(a);
}

lval *lval_copy(lval *a) {
    lval *r = malloc(sizeof(lval));
    r->type = a->type;
    switch (a->type) {
        case LTYPE_NUM:
            r->num = a->num;
            break;
        case LTYPE_SYM:
            r->sym = malloc(sizeof(strlen(a->sym) + 1));
            strcpy(r->sym, a->sym);
            break;
        case LTYPE_ERR:
            r->err = malloc(sizeof(strlen(a->err) + 1));
            strcpy(r->err, a->err);
            break;
        case LTYPE_STR:
            r->str = malloc(sizeof(strlen(a->str) + 1));
            strcpy(r->str, a->str);
            break;
        case LTYPE_SEXPR:
            r->count = a->count;
            r->elem = malloc(sizeof(lval *) * a->count);
            for (int i = 0; i < a->count; i++) {
                r->elem[i] = lval_copy(a->elem[i]);
            }
            break;
        case LTYPE_QEXPR:
            r->tar = lval_copy(a->tar);
            break;
        default:
            lval_del(r);
            break;
    }
    return r;
}

lval *lval_add(lval *d, lval *v) {
    d->count++;
    d->elem = realloc(d->elem, sizeof(lval) * d->count);
    d->elem[d->count - 1] = lval_copy(v);
    return d;
}
