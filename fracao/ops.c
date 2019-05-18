#ifndef CN_FRACAO_OPS
#define CN_FRACAO_OPS
#include <stdio.h>
#include "./struct.c"

double
cn_fracao__as_double(struct cn_fracao this) {
    return (double)this.numerador / (double)this.denominador;
}

struct cn_fracao 
cn_fracao__sum(
        struct cn_fracao a,
        struct cn_fracao b
) {
    struct cn_fracao res;
    res.denominador = a.denominador == b.denominador
        ? a.denominador
        : a.denominador * b.denominador;
    int numa = a.numerador * (res.denominador / a.denominador);
    int numb = b.numerador * (res.denominador / b.denominador);
    res.numerador = numa + numb;
    return res;
}

struct cn_fracao 
cn_fracao__sub(
        struct cn_fracao a,
        struct cn_fracao b
) {
    struct cn_fracao res;
    res.denominador = a.denominador == b.denominador
        ? a.denominador
        : a.denominador * b.denominador;
    int numa = a.numerador * (res.denominador / a.denominador);
    int numb = b.numerador * (res.denominador /b.denominador);
    res.numerador = numa - numb;
    return res;
}

struct cn_fracao
cn_fracao__mul(
        struct cn_fracao a,
        struct cn_fracao b
) {
    struct cn_fracao res;
    res.numerador = a.numerador * b.numerador;
    res.denominador = a.denominador * b.denominador;
    return res;
}

struct cn_fracao
cn_fracao__div(
        struct cn_fracao a,
        struct cn_fracao b
) {
    struct cn_fracao res;
    res.numerador = a.numerador * b.denominador;
    res.denominador = a.denominador * b.numerador;
    return res;
}

void
cn_fracao__prettyprint(
        struct cn_fracao f
) {
    printf("FRACAO(%i/%i)", f.numerador, f.denominador);
}

int
cn_fracao__cmp(
        struct cn_fracao a,
        struct cn_fracao b
) {
    struct cn_fracao div = cn_fracao__div(a,b);
    return div.denominador == div.numerador;
}


#endif
