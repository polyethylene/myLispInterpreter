#ifndef SOURCE_BUILTIN_H
#define SOURCE_BUILTIN_H

#include "headers.h"

/* builtin algebra operation */

lval *builtin_add(lenv *, lval *);

lval *builtin_sub(lenv *, lval *);

lval *builtin_mul(lenv *, lval *);

lval *builtin_div(lenv *, lval *);

lval *builtin_op(lval *, char *op);

/* builtin list operation */

lval *builtin_list(lenv *, lval *);

lval *builtin_head(lenv *, lval *);

lval *builtin_tail(lenv *, lval *);

/* builtin lambda operation */

lval *builtin_lambda(lenv *, lval *);

lval *builtin_def(lenv *, lval *);

lval *builtin_def_fun(lenv *, lval *);

lval *builtin_def_sym(lenv *, lval *);

/* builtin compare operation */

lval *builtin_gt(lenv *, lval *);

lval *builtin_lt(lenv *, lval *);

lval *builtin_egt(lenv *, lval *);

lval *builtin_elt(lenv *, lval *);

lval *builtin_cmp(lval *, char *);

int test_eq(lval *, lval *);

lval *builtin_eq(lenv *, lval *);

lval *builtin_neq(lenv *, lval *);

/* builtin conditional operation */

lval *builtin_if(lenv *, lval *);

/* builtin bool operation */

lval *builtin_and(lenv *, lval *);

lval *builtin_or(lenv *, lval *);

lval *builtin_not(lenv *, lval *);

/* builtin file read operation */

lval *builtin_load(lenv *, lval *);

lval *builtin_eval(lenv *, lval *);

void lenv_add_builtin(lenv *, char *, builtin_fun *);

void lenv_add_builtins(lenv *);

#endif //SOURCE_BUILTIN_H
