function sair() {
    echo "SAINDO: $1"
    exit 1
}

function test_module() {
    echo "Compilando teste do módulo $1..."
    gcc $1/test.c -o test_$1 -Wall
    echo "Rodando teste do módulo $1..."
    ./test_$1 || sair "Teste $1 falhou!"
}
case $1 in
    test)
        test_module fracao
        test_module matriz
        ;;
esac
