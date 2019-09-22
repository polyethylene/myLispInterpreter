#include "builtin.h"

lval *builtin_add(lenv *env, lval *a) {
    return builtin_op(a, "+");
}

lval *builtin_sub(lenv *env, lval *a) {
    return builtin_op(a, "-");
}

lval *builtin_mul(lenv *env, lval *a) {
    return builtin_op(a, "*");
}

lval *builtin_div(lenv *env, lval *a) {
    return builtin_op(a, "/");
}

lval *builtin_op(lval *a, char *op) {
    if ((strcmp(op, "*") == 0 || strcmp(op, "/") == 0) && a->count < 2) {
        return lval_err("Operator '%s' got too less arguments. Got %i, Expected more than 1.", op, a->count);
    }
    for (int i = 0; i < a->count; i++) {
        LASSERT_TYPE(op, a, i, LTYPE_NUM);
    }

    lval *x = lval_pop(a, 0);

    if ((strcmp(op, "-") == 0) && a->count == 0) {
        x->num = -x->num;
    }

    while (a->count > 0) {
        lval *y = lval_pop(a, 0);
        if (strcmp(op, "+") == 0) { x->num += y->num; }
        if (strcmp(op, "-") == 0) { x->num -= y->num; }
        if (strcmp(op, "*") == 0) { x->num *= y->num; }
        if (strcmp(op, "/") == 0) {
            if (y->num == 0) {
                lval_del(x);
                lval_del(y);
                x = lval_err("Division By Zero!");
                break;
            }
            x->num /= y->num;
        }
        lval_del(y);
    }
    lval_del(a);
    return x;
}

/* define list operation */

lval *builtin_list(lenv *env, lval *v) {
    lval *r = lval_qexpr();
    r->tar = lval_copy(v);
    return r;
}

lval *builtin_head(lenv *env, lval *v) {
    LASSERT_NUM("head", v, 1);
    LASSERT_TYPE("head", v, 0, LTYPE_QEXPR);
    lval *a = lval_take(v, 0);
    lval *r = lval_copy(a->tar);
    lval_del(a);
    return r;
}

lval *builtin_tail(lenv *env, lval *v) {
    LASSERT_NUM("tail", v, 1);
    LASSERT_TYPE("tail", v, 0, LTYPE_QEXPR);
    lval *a = lval_take(v, 0);
    lval *r = lval_copy(a->tar);
    lval_del(a);
    lval *d = lval_pop(r, 0);
    lval_del(d);
    return r;
}

lval *builtin_lambda(lenv *env, lval *v) {
    LASSERT_NUM("lambda", v, 2);
    LASSERT_TYPE("lambda", v, 0, LTYPE_QEXPR);
    LASSERT_TYPE("lambda", v, 1, LTYPE_QEXPR);

    for (int i = 0; i < v->elem[0]->tar->count; i++) {
        LASSERT(v, (v->elem[0]->tar->elem[i]->type == LTYPE_SYM),
                "Function lambda : argruments can't be non-symbol. Got %s, Expected %s.",
                ltype_name(v->elem[0]->tar->elem[i]->type), ltype_name(LTYPE_SYM));
    }

    lval *args = lval_pop(v, 0);
    lval *body = lval_pop(v, 0);
    lval_del(v);
    lval *l = lval_lambda(args, body);
    lval_del(args);
    lval_del(body);
    return l;
}

lval *builtin_def(lenv *env, lval *v) {
    LASSERT_NUM("define", v, 2);
    LASSERT_TYPE("define", v, 0, LTYPE_QEXPR);
    LASSERT_TYPE("define", v, 1, LTYPE_QEXPR);

    LASSERT(v, (v->elem[0]->tar->elem[0]->type == LTYPE_SYM),
            "Function lambda : cannot define non-symbol. Got %s, Expected %s.",
            ltype_name(v->elem[0]->tar->elem[0]->type), ltype_name(LTYPE_SYM));

    return builtin_def_fun(env, v);
}

lval *builtin_def_fun(lenv *env, lval *v) {
    /* get the function name */
    lval *name = lval_pop(v->elem[0]->tar, 0);

    /* create an lambda variable */
    lval *f = builtin_lambda(env, v);
    /* catch the non-symbol-error */
    if (f->type == LTYPE_ERR) {
        return f;
    }

    /* link the name and the variable in the current environment (local variable) */
    lenv_put(env, name, f);
    return lval_sexpr();
}

lval *builtin_eval(lenv *env, lval *v) {
    LASSERT_NUM("eval", v, 1)
    LASSERT_TYPE("eval", v, 0, LTYPE_QEXPR);
    lval *q = lval_take(v, 0);
    lval *r = lval_copy(q->tar);
    return lval_eval(env, r);
}

lval *builtin_gt(lenv *env, lval *v) {
    return builtin_cmp(v, ">");
}

lval *builtin_lt(lenv *env, lval *v) {
    return builtin_cmp(v, "<");
}

lval *builtin_cmp(lval *v, char *op) {
    LASSERT_NUM(op, v, 2);
    LASSERT_TYPE(op, v, 0, LTYPE_NUM);
    LASSERT_TYPE(op, v, 1, LTYPE_NUM);
    lval *lhs = lval_pop(v, 0);
    lval *rhs = lval_take(v, 0);
    int l = lhs->num, r = rhs->num, result = 0;
    lval_del(lhs);
    lval_del(rhs);
    if (strcmp(op, ">") == 0) { result = l > r; }
    else if (strcmp(op, ">=") == 0) { result = l >= r; }
    else if (strcmp(op, "<") == 0) { result = l < r; }
    else if (strcmp(op, "<=") == 0) { result = l <= r; }
    if (result) {
        return lval_bool(LBOOL_TRUE);
    } else {
        return lval_bool(LBOOL_FALSE);
    }
}

void lenv_add_builtin(lenv *env, char *a, builtin_fun *b) {
    lval *s = lval_sym(a);
    lval *f = lval_fun(b);
    lenv_put(env, s, f);
    lval_del(s);
    lval_del(f);
}

void lenv_add_builtins(lenv *e) {
    lenv_add_builtin(e, "+", builtin_add);
    lenv_add_builtin(e, "-", builtin_sub);
    lenv_add_builtin(e, "*", builtin_mul);
    lenv_add_builtin(e, "/", builtin_div);

    lenv_add_builtin(e, "list", builtin_list);
    lenv_add_builtin(e, "head", builtin_head);
    lenv_add_builtin(e, "tail", builtin_tail);

    lenv_add_builtin(e, "eval", builtin_eval);
    lenv_add_builtin(e, "define", builtin_def);
    lenv_add_builtin(e, "lambda", builtin_lambda);

    lenv_add_builtin(e, ">", builtin_gt);
    lenv_add_builtin(e, "<", builtin_lt);
}
