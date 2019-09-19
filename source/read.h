#ifndef SOURCE_READ_H
#define SOURCE_READ_H

#include "mpc.h"

lval **lval_read(mpc_ast_t *, int *);

lval *lval_read_number(mpc_ast_t *);

lval *lval_read_string(mpc_ast_t *);

void lval_print_single(lval *);

void lval_print(int, lval **);

#endif