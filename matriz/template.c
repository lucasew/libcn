#ifndef CN_MATRIZ_TEMPLATE
#define CN_MATRIZ_TEMPLATE

#include "./struct.c"
#include "./ops.c"
#include "../status.h"

int cn_matriz__init_identity(struct cn_matriz *this, int order) {
    if (cn_matriz__init(this, order, order) == ERROR)
        return ERROR;
    int i;
    for (i = 0; i < order; i++) {
        if (cn_matriz__set(this, i, i, 1) == ERROR)
            return ERROR;
    }
    return SUCESS;
}
 #endif
