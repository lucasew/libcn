#ifndef CN_CHOLESKY
#define CN_CHOLESKY
#include "../fracao/ops.c"
#include "../fracao/ops_sqrt.c"
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

int cn_cholesky__calc(struct cn_matriz *this, struct cn_matriz *res) {
    if (!cn_cholesky__check(this))
        return ERROR;
    cn_matriz__init(res, this->tam_i, this->tam_j);

    int i, j, k;
    for (i = 0; i < this->tam_i; i++)
        for (j = 0; j < (i + 1); j++) {
            struct cn_fracao soma = cn_fracao__zero();
            for (k = 0; k < j; k++)
                soma = cn_fracao__sum(soma,
                        cn_fracao__mul(
                            res->vet[i*res->tam_i + k],
                            res->vet[j*res->tam_i + k]
                            )
                        );
                res->vet[i*res->tam_i + j] = (i == j)
                    ? cn_fracao__sqrt(
                            cn_fracao__sub(this->vet[i*this->tam_i + i], soma))
                    : cn_fracao__div(
                            cn_fracao__init(1,1),
                                cn_fracao__mul(
                                    res->vet[j*res->tam_i + j],
                                    cn_fracao__sub(
                                        this->vet[i*res->tam_i + j],
                                        soma
                                        )
                                    )
                            );
            }
    return SUCESS;
}

#endif
