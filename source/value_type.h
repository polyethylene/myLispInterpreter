#ifndef VALUE_TYPE
#define VALUE_TYPE

/* tag of lisp value type */

enum {LTYPE_NUM,LTYPE_SYM,LTYPE_STR,
        LTYPE_SEXPR,LTYPE_QEXPR,LTYPE_FUN};

/* lisp value type and lisp environment*/

typedef struct lval lval;
typedef struct lenv lenv;

/*  lisp builtin-function */

typedef lval* builtin_fun(lenv*,lval*);

struct lval{
    /* basic type */
    int type;           //type of the value
    int num;            //for number
    char* sym;          //for symbol
    char* str;          //for string

    int count;          //both q/s expression and function will use this
    /* q or s expression */
    lval** elem;

    /* function */
    builtin_fun* builtin;
    lenv* par;
    char** args;
    lval* body;
};

/* definition of environment, will be changed into hash_table */

struct lenv{
    int count;
    char** sym;
    lval** val;
};

#endif
