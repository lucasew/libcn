#ifndef CN_FRACAO_STRUCT
#define CN_FRACAO_STRUCT

struct cn_fracao {
    int numerador;
    int denominador;
};

struct cn_fracao cn_fracao__init(int num, int den) {
    struct cn_fracao fr;
    fr.numerador = num;
    fr.denominador = den;
    return fr;
}

struct cn_fracao cn_fracao__zero() {
    return cn_fracao__init(0, 1);
}

#endif
