#ifndef CN_CHOLESKY
#define CN_CHOLESKY
#include "../fracao/ops.c"
#include "../matriz/ops.c"
#include "../matriz/struct.c"
int cn_cholesky__check(struct cn_matriz *this) {
    if (!cn_matriz__is_quadrada(this))
            return 0;
    int i;
    for (i = 1; i < this->tam_i; i++) {
        struct cn_fracao det;
        struct cn_matriz menores;
        if (cn_matriz__get_menor_principal(this, &menores, i) == ERROR)
            return 0;
        if (cn_matriz__get_determinante(&menores, &det) == ERROR)
            return 0;
        if (det.numerador*det.denominador <= 0)
            return 0;
    }
    return 1;
}


#endif
