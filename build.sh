function sair() {
    echo "SAINDO: $1"
    exit 1
}

function test_module() {
    echo "Compilando teste do módulo $1..."
    gcc $1/test.c -o test_$1 -Wall -lm
    echo "Rodando teste do módulo $1..."
    ./test_$1 || sair "Teste $1 falhou!"
}
case $1 in
    test)
        test_module cholesky
        test_module matriz
        test_module alu
        ;;
esac
