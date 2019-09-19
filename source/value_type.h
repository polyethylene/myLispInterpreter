#ifndef SOURCE_VALUE_TYPE_H
#define SOURCE_VALUE_TYPE_H

/* tag of lisp value type */

enum {
    LTYPE_NUM, LTYPE_SYM, LTYPE_ERR, LTYPE_STR,
    LTYPE_SEXPR, LTYPE_QEXPR, LTYPE_FUN
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
    int type;           //type of the value
    int num;            //for number
    char *sym;          //for symbol
    char *err;          //for error
    char *str;          //for string

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

lval *lval_sexpr();

lval *lval_qexpr();

lval *lval_fun();

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

/* operation of link list */

lval_link_list *new_link_list();

void del_link_list(lval_link_list *);

void link_list_insert(lval_link_list *, int, lval *);

void link_list_delete(lval_link_list *, int);

void link_list_push_front(lval_link_list *, lval *);

void link_list_pop_front(lval_link_list *, lval *);

void link_list_push_back(lval_link_list *, lval *);

void link_list_pop_back(lval_link_list *, lval *);

lval *link_list_get(lval_link_list *, int);


/* addition function */
char *ltype_name(int);

#endif
