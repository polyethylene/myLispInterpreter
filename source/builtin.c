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
    lval *r = lval_take(v->elem[0]->tar, 0);
    return r;
}

lval *builtin_tail(lenv *env, lval *v) {
    LASSERT_NUM("tail", v, 1);
    LASSERT_TYPE("tail", v, 0, LTYPE_QEXPR);
    lval *p = lval_pop(v->elem[0]->tar, 0);
    lval_del(p);
    return v->elem[0];
}

lval *builtin_lambda(lenv *env, lval *v) {
    LASSERT_NUM("lambda", v, 2);
    LASSERT_TYPE("lambda", v, 0, LTYPE_SEXPR);

    for (int i = 0; i < v->elem[0]->count; i++) {
        LASSERT(v, (v->elem[0]->elem[i]->type == LTYPE_SYM),
                "Function lambda : cannot define non-symbol. Got %s, Expected %s.",
                ltype_name(v->elem[0]->elem[i]->type), ltype_name(LTYPE_SYM));
    }

    lval *f = lval_fun(NULL);
    f->env = lenv_new();
    f->env->par = env;
    f->args = lval_copy(v->elem[0]);
    f->body = lval_copy(v->elem[1]);
    return f;
}

lval *builtin_def(lenv *env, lval *v) {
    LASSERT_NUM("define", v, 2);
    if (v->elem[0]->type == LTYPE_SYM) {
        lenv_put(env, v->elem[0], v->elem[1]);
    }
    if (v->elem[0]->type == LTYPE_SEXPR) {

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
}
