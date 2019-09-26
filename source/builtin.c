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
    lval *r = lval_pop(a->tar, 0);
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

    if (v->elem[0]->tar->type == LTYPE_SYM) {
        return builtin_def_sym(env, v);
    } else {
        return builtin_def_fun(env, v);
    }
}

lval *builtin_def_sym(lenv *env, lval *v) {
    LASSERT_TYPE("define(symbol)", v, 0, LTYPE_QEXPR);
    lval *t = lval_pop(v, 0);
    lval *name = t->tar;
    lval_del(t);

    LASSERT(name, (name->type == LTYPE_SYM),
            "Function define : cannot define non-symbol. Got %s, Expected %s.",
            ltype_name(name->type), ltype_name(LTYPE_SYM));

    lval *val = lval_take(v, 0);
    lenv_put(env, name, val);
    return lval_sexpr();
}

lval *builtin_def_fun(lenv *env, lval *v) {
    LASSERT_TYPE("define(function)", v, 0, LTYPE_QEXPR);
    LASSERT_TYPE("define(function)", v, 1, LTYPE_QEXPR);

    LASSERT(v, (v->elem[0]->tar->elem[0]->type == LTYPE_SYM),
            "Function define : cannot define non-symbol. Got %s, Expected %s.",
            ltype_name(v->elem[0]->tar->elem[0]->type), ltype_name(LTYPE_SYM));

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

lval *builtin_egt(lenv *env, lval *v) {
    return builtin_cmp(v, ">=");
}

lval *builtin_elt(lenv *env, lval *v) {
    return builtin_cmp(v, "<=");
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
    return lval_bool(result);
}

int test_eq(lval *lhs, lval *rhs) {
    if (lhs->type != rhs->type) {
        return 0;
    }
    switch (lhs->type) {
        case LTYPE_NUM:
            return lhs->num == rhs->num;
        case LTYPE_SYM:
            return strcmp(lhs->sym, rhs->sym) == 0;
        case LTYPE_STR:
            return strcmp(lhs->sym, rhs->sym) == 0;
        case LTYPE_BOOL:
            return lhs->bval == rhs->bval;
        case LTYPE_FUN:
            if (lhs->builtin) {
                return lhs->builtin == rhs->builtin;
            }
            if (rhs->builtin) {
                return 0;
            }
            return test_eq(lhs->args, rhs->args) &&
                   test_eq(lhs->body, rhs->body);
        case LTYPE_SEXPR:
            if (lhs->count != rhs->count) {
                return 0;
            }
            for (int i = 0; i < lhs->count; i++) {
                if (!test_eq(lhs->elem[i], rhs->elem[i])) {
                    return 0;
                }
            }
            return 1;
        case LTYPE_QEXPR:
            return test_eq(lhs->tar, rhs->tar);
        case LTYPE_ERR:
            return strcmp(lhs->err, rhs->err) == 0;
        default:
            break;
    }
    return 0;
}

lval *builtin_eq(lenv *env, lval *v) {
    LASSERT_NUM("==", v, 2);
    lval *lhs = lval_pop(v, 0);
    lval *rhs = lval_take(v, 0);
    int res = test_eq(lhs, rhs);
    lval_del(lhs);
    lval_del(rhs);
    return lval_bool(res);
}

lval *builtin_neq(lenv *env, lval *v) {
    LASSERT_NUM("==", v, 2);
    lval *lhs = lval_pop(v, 0);
    lval *rhs = lval_take(v, 0);
    int res = test_eq(lhs, rhs);
    lval_del(lhs);
    lval_del(rhs);
    return lval_bool(!res);
}

lval *builtin_and(lenv *env, lval *v) {
    for (int i = 0; i < v->count; i++) {
        LASSERT_TYPE("and", v, i, LTYPE_BOOL);
    }
    lval *r = lval_bool(1);
    for (int i = 0; i < v->count; i++) {
        if (v->elem[i]->bval == LBOOL_FALSE) {
            r->bval = LBOOL_FALSE;
            break;
        }
    }
    lval_del(v);
    return r;
}

lval *builtin_or(lenv *env, lval *v) {
    for (int i = 0; i < v->count; i++) {
        LASSERT_TYPE("or", v, i, LTYPE_BOOL);
    }
    lval *r = lval_bool(0);
    for (int i = 0; i < v->count; i++) {
        if (v->elem[i]->bval == LBOOL_TRUE) {
            r->bval = LBOOL_TRUE;
            break;
        }
    }
    lval_del(v);
    return r;
}

lval *builtin_not(lenv *env, lval *v) {
    LASSERT_NUM("not", v, 1);
    LASSERT_TYPE("not", v, 0, LTYPE_BOOL);
    lval *r = lval_bool(1);
    if (v->elem[0]->bval == LBOOL_TRUE) {
        r->bval = LBOOL_FALSE;
    } else {
        r->bval = LBOOL_TRUE;
    }
    lval_del(v);
    return r;
}

lval *builtin_if(lenv *env, lval *v) {
    LASSERT_NUM("if", v, 3);
    LASSERT_TYPE("if", v, 0, LTYPE_BOOL);
    LASSERT_TYPE("if", v, 1, LTYPE_QEXPR);
    LASSERT_TYPE("if", v, 1, LTYPE_QEXPR);
    lval *cond = lval_pop(v, 0);
    if (cond->bval == LBOOL_TRUE) {
        lval_del(cond);
        return builtin_eval(env, lval_add(lval_sexpr(), lval_take(v, 0)));
    } else {
        lval_del(cond);
        return builtin_eval(env, lval_add(lval_sexpr(), lval_take(v, 1)));
    }
}

lval *builtin_load(lenv *env, lval *v) {
    mpc_result_t t;

    /* read all files */
    for (int i = 0; i < v->count; i++) {
        LASSERT_TYPE("load", v, i, LTYPE_STR);
        if (mpc_parse_contents(v->elem[i]->str, Lisp, &t)) {
            /*just like the main function */
            lval **cur = NULL;
            int num = 0;
            cur = lval_read(t.output, &num);
            mpc_ast_delete(t.output);
            for (int j = 0; j < num; j++) {
                lval_eval(env, cur[j]);
            }
        } else {
            char *err_msg = mpc_err_string(t.error);
            mpc_err_delete(t.error);

            /* Create new error message using it */
            lval *err = lval_err("Could not load Library %s", err_msg);
            free(err_msg);
            lval_del(v);

            /* Cleanup and return error */
            return err;
        }
    }
    return lval_sexpr();
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
    lenv_add_builtin(e, ">=", builtin_egt);
    lenv_add_builtin(e, "<=", builtin_elt);
    lenv_add_builtin(e, "==", builtin_eq);
    lenv_add_builtin(e, "!=", builtin_neq);

    lenv_add_builtin(e, "if", builtin_if);

    lenv_add_builtin(e, "and", builtin_and);
    lenv_add_builtin(e, "or", builtin_or);
    lenv_add_builtin(e, "not", builtin_not);

    lenv_add_builtin(e, "load", builtin_load);

    /* builtin_symbol */
    lenv_put(e, lval_sym("TRUE"), lval_bool(1));
    lenv_put(e, lval_sym("FALSE"), lval_bool(0));
}
