#ifndef VARLIST_H
#define VARLIST_H

#include <stdbool.h>

void var_list_add( char *name, int value );
bool var_list_get( char *name, int *value );

#endif // VARLIST_H
