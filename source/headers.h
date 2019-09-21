#ifndef SOURCE_HEADERS_H
#define SOURCE_HEADERS_H

#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"
#include "value_type.h"
#include "read.h"
#include "eval.h"
#include "builtin.h"

#ifdef _WIN32

#include <string.h>

#endif

#define LASSERT(args, cond, fmt, ...) \
  if (!(cond)) { lval* err = lval_err(fmt, ##__VA_ARGS__); lval_del(args); return err; }

#define LASSERT_TYPE(func, args, index, expect) \
  LASSERT(args, args->elem[index]->type == expect, \
    "Function '%s' passed incorrect type for argument %i. " \
    "Got %s, Expected %s.", \
    func, index, ltype_name(args->elem[index]->type), ltype_name(expect))

#define LASSERT_NUM(func, args, num) \
  LASSERT(args, args->count == num, \
    "Function '%s' passed incorrect number of arguments. " \
    "Got %i, Expected %i.", \
    func, args->count, num)

#endif //SOURCE_HEADERS_H
