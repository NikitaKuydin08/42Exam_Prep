#ifndef VBC_H
# define VBC_H

typedef struct  node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#endif