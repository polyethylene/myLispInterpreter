#ifndef SOURCE_EVAL_H
#define SOURCE_EVAL_H

#include "value_type.h"

lval *lval_eval(lenv *, lval *);

lval *lval_eval_sexpr(lenv *, lval *);

lval *lval_call(lenv *, lval *, lval *);

#endif
