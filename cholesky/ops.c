#ifndef CN_CHOLESKY
#define CN_CHOLESKY
#include "../matriz/ops.c"
#include "../matriz/struct.c"
#include <math.h>
int cn_cholesky__check(struct cn_matriz *this) {
    if (!cn_matriz__is_quadrada(this))
        return 0;
    int i;
    for (i = 1; i < this->tam_i; i++) {
        double det;
        struct cn_matriz menores;
        if (cn_matriz__get_menor_principal(this, &menores, i) == ERROR)
            return 0;
        if (cn_matriz__get_determinante(&menores, &det) == ERROR)
            return 0;
        if (det <= 0)
            return 0;
    }
    return 1;
}

int cn_cholesky__calc(struct cn_matriz *this, struct cn_matriz *res) {
    if (!cn_cholesky__check(this))
        return ERROR;
    cn_matriz__init(res, this->tam_i, this->tam_j);

    int i, j, k;
    for (i = 0; i < this->tam_i; i++)
        for (j = 0; j < (i + 1); j++) {
            double soma = 0;
            for (k = 0; k < j; k++)
                soma += res->vet[i*res->tam_i + k] * res->vet[j*res->tam_i + k];
            res->vet[i*res->tam_i + j] = (i == j)
                ? sqrt(this->vet[i*this->tam_i + i] - soma)
                : 1.0/
                res->vet[j*res->tam_i + j]
                 * (this->vet[i*res->tam_i + j] - soma);
        }
    return SUCESS;
}

#endif
