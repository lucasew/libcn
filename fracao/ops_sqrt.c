#ifndef CN_FRACAO_OPS_SQRT
#define CN_FRACAO_OPS_SQRT
#include "./ops.c"
#include "./struct.c"
#include <math.h>
#include <stdlib.h>

struct cn_fracao
cn_fracao__sqrt(
        struct cn_fracao this
) {
    double valor = sqrt((double)this.numerador/(double)this.denominador);
    printf("VALOR: %lf\n", valor);
    struct cn_fracao ret = cn_fracao__zero();
    int k = 0;
    int asint;
    do {
        valor*= 2;
        ret.denominador *= 2;
        int asint = (int)valor;
        printf("V: %lf DEN: %i\n", valor, ret.denominador);
        k++;
    } while (fabs((double)(valor - (double)asint)) > 0.001 && k < 10);
    ret.numerador = (int)valor;
    return ret;
}

#endif
