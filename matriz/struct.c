#ifndef CN_MATRIZ_STRUCT
#define CN_MATRIZ_STRUCT
#include <stdlib.h>
#include "../fracao/struct.c"
#include "../status.h"

struct cn_matriz {
    struct cn_fracao *vet;
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
    this->vet = calloc(tam_i*tam_j, sizeof(struct cn_fracao));
    if (this->vet == NULL) {
        return ERROR;
    }
    int i;
    struct cn_fracao template = {0, 1};
    for (i = 0; i < this->tam_i*this->tam_j; i++) {
        this->vet[i] = template;
    }
    return SUCESS;
}

int
cn_matriz__destroy(struct cn_matriz *this) {
    free(this->vet);
    return SUCESS;
}


#endif
