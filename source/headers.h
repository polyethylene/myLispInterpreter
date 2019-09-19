#ifndef SOURCE_HEADERS_H
#define SOURCE_HEADERS_H

#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"
#include "value_type.h"
#include "read.h"

#ifdef _WIN32

#include <string.h>

static char buffer[2048];

char *readline(char *prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char *cpy = malloc(strlen(buffer) + 1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy) - 1] = '\0';
    return cpy;
}

void add_history(char *unused) {}

#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

#endif //SOURCE_HEADERS_H
