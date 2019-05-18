#ifndef CN_MATRIZ_STRUCT
#define CN_MATRIZ_STRUCT
#include <stdlib.h>
#include "../status.h"

struct cn_matriz {
    double *vet;
    int tam_i;
    int tam_j;
};

int
cn_matriz__init(
    struct cn_matriz *this,
    int tam_i, int tam_j
) {
    this->tam_i = tam_i;
    this->tam_j = tam_j;
    this->vet = calloc(tam_i*tam_j, sizeof(double));
    if (this->vet == NULL) {
        return ERROR;
    }
    return SUCESS;
}

int
cn_matriz__destroy(struct cn_matriz *this) {
    free(this->vet); // Pode ser NULL, não faz mal
    this->vet = NULL;
    this->tam_i = 0;
    this->tam_j = 0;
    return SUCESS;
}


#endif
