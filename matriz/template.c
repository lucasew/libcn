#ifndef CN_MATRIZ_TEMPLATE
#define CN_MATRIZ_TEMPLATE

#include "./struct.c"
#include "./ops.c"
#include "../status.h"

int cn_matriz__init_identity(int order, struct cn_matriz *this) {
    if (cn_matriz__init(this, order, order) == ERROR)
        return ERROR;
    int i;
    struct cn_fracao one = cn_fracao__init(1, 1);
    for (i = 0; i < order; i++) {
        if (cn_matriz__set(this, i, i, one) == ERROR)
            return ERROR;
    }
    return SUCESS;
}
 #endif
