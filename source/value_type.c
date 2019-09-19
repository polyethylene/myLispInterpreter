#include "headers.h"

#define env e

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

lval *lval_err(char *fmt, ...) {
    lval *r = malloc(sizeof(lval));
    r->type = LTYPE_ERR;

    va_list va;
    va_start(va, fmt);

    r->err = malloc(512);

    vsnprintf(r->err, 511, fmt, va);

    r->err = realloc(r->err, strlen(r->err) + 1);
    va_end(va);
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

/* return the name of type (for error format print) */
char *ltype_name(int type) {
    switch (type) {
        case LTYPE_NUM:
            return "Number";
        case LTYPE_SYM:
            return "Symbol";
        case LTYPE_ERR:
            return "Error";
        case LTYPE_FUN:
            return "Function";
        case LTYPE_STR:
            return "String";
        case LTYPE_SEXPR:
            return "S-expression";
        case LTYPE_QEXPR:
            return "Q-expression";
        default:
            return "Unknown";
    }
}


/* put new pairs into environment */
void lenv_put(lenv *env, lval *s, lval *v) {
    for (int i = 0; i < env->count; i++) {
        /* if there is one same symbol in the environment, redefine it */
        if (strcmp(env->syms[i], s->sym) == 0) {
            lval_del(env->vals[i]);
            env->vals[i] = lval_copy(v);
            return;
        }
    }
    env->count++;

    /* allocate new memory for environment */
    env->syms = realloc(env->syms, sizeof(char *) * env->count);
    env->vals = realloc(env->vals, sizeof(lval *) * env->count);

    /* allocate new memory for symbol string and copy it */
    env->syms[env->count - 1] = malloc(strlen(s->sym) + 1);
    strcpy(env->syms[env->count - 1], s->sym);

    /* copy new value into environment (has allocated in lval_copy) */
    env->vals[env->count - 1] = lval_copy(v);
}
