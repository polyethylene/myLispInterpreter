//
// Created by 聚乙烯 on 2019/9/19.
//
#include "headers.h"

lval *lval_eval(lenv *env, lval *v) {
    if (v->type == LTYPE_SYM) {
        lval *r = lenv_get(env, v);
        lval_del(v);
        return r;
    }
    if (v->type == LTYPE_SEXPR) {
        return lval_eval_sexpr(env, v);
    }
    return v;
}

lval *lval_eval_sexpr(lenv *env, lval *v) {
    /* evaluate all subexpression first */
    for (int i = 0; i < v->count; i++) {
        v->elem[i] = lval_eval(env, v->elem[i]);
    }

    /* check whether there is an error, if there is one, take it */
    for (int i = 0; i < v->count; i++) {
        if (v->type == LTYPE_ERR) {
            return lval_take(v, i);
        }
    }

    if (v->count == 0) {
        return v;
    }
    if (v->count == 1) {
        return lval_take(v, 0);
    }

    lval *f = lval_pop(v, 0);
    if (f->type != LTYPE_FUN) {
        lval *err = lval_err(
                "S-Expression starts with incorrect type. "
                "Got %s, Expected %s.",
                ltype_name(f->type), ltype_name(LTYPE_FUN));
        lval_del(f);
        lval_del(v);
        return err;
    }
    /* f is always a function type and v is a sexpression that hold all argutments */
    lval *result = lval_call(env, f, v);
    return result;
}

lval *lval_call(lenv *env, lval *fun, lval *v) {
    if (fun->builtin) {
        return fun->builtin(env, v);
    }

    int get = v->count;
    int total = fun->args->count;
    while (v->count) {
        if (fun->args->count == 0) {
            lval_del(v);
            return lval_err("Function get too many arguments. Got %i, expected %i", get, total);
        }
        lval *sym = lval_pop(fun->args, 0);
        lval *act = lval_pop(v, 0);

        if (strcmp(sym->sym, "&") == 0) {
            /* Ensure '&' is followed by another symbol */
            if (fun->args->count != 1) {
                lval_del(v);
                return lval_err("Function format invalid. "
                                "Symbol '&' not followed by single symbol.");
            }
            /* Next formal should be bound to remaining arguments */
            lval *nsym = lval_pop(fun->args, 0);
            //lenv_put(fun->env, nsym, builtin_list(env, v));
            lval_del(sym);
            lval_del(nsym);
            break;
        }
        lenv_put(fun->env, sym, act);
        lval_del(sym);
        lval_del(act);
    }
}

