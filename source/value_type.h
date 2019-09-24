#ifndef SOURCE_VALUE_TYPE_H
#define SOURCE_VALUE_TYPE_H

typedef enum lbool lbool;
typedef enum ltype ltype;

/* lisp bool value */
enum lbool {
    LBOOL_TRUE, LBOOL_FALSE
};


/* tag of lisp value type */

enum ltype {
    LTYPE_NUM, LTYPE_SYM, LTYPE_ERR, LTYPE_STR,
    LTYPE_SEXPR, LTYPE_QEXPR, LTYPE_FUN, LTYPE_BOOL
};

/* declaration of lisp value type and lisp environment*/

typedef struct lval lval;
typedef struct lenv lenv;

/* declaration of lisp value data structure */

typedef struct lval_list_node lval_list_node;
typedef struct lval_link_list lval_link_list;

/* definition of lisp builtin-function */

typedef lval *builtin_fun(lenv *, lval *);

struct lval {
    /* basic type */
    ltype type;           //type of the value
    int num;            //for number
    char *sym;          //for symbol
    char *err;          //for error
    char *str;          //for string
    lbool bval;           //for bool

    /* q expression */
    lval *tar;

    /* s expression */
    int count;
    lval **elem;

    /* function */
    builtin_fun *builtin;
    lenv *env;
    lval *args;
    lval *body;
};

/* definition of environment, will be changed into hash_table */

struct lenv {
    lenv *par;

    int count;
    char **syms;
    lval **vals;
};

/* definition of lisp value data structure */

struct lval_list_node {
    lval_list_node *next;
    lval_list_node *prev;
    lval *val;
};

struct lval_link_list {
    int count;
    lval_list_node *head;
    lval_list_node *tail;
};

/* declaration of construct function */

lval *lval_num(int);

lval *lval_sym(char *);

lval *lval_err(char *, ...);

lval *lval_str(char *);

lval *lval_bool(int);

lval *lval_sexpr();

lval *lval_qexpr();

lval *lval_fun(builtin_fun);

lval *lval_lambda(lval *, lval *);

lenv *lenv_new();


/* operation of lisp value */

void lval_del(lval *);

lval *lval_copy(lval *);

lval *lval_add(lval *, lval *);

lval *lval_pop(lval *, int);

lval *lval_take(lval *, int);

lval *lval_join(lval *, lval *);


/* operation of enviroment */

lval *lenv_get(lenv *, lval *);

void lenv_del(lenv *);

void lenv_put(lenv *, lval *, lval *);

lenv *lenv_copy(lenv *);


/* addition function */
char *ltype_name(ltype);

#endif
