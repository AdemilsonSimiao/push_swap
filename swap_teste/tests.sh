#!/bin/bash

PS=./push_swap

echo "=============================="
echo "TESTES BÁSICOS"
echo "=============================="

echo
echo "2 elementos"
$PS --bench --simple 2 1

echo
echo "3 elementos"
$PS --bench --simple 3 2 1
$PS --bench --simple 2 3 1
$PS --bench --simple 1 3 2
$PS --bench --simple 3 1 2
$PS --bench --simple 2 1 3
$PS --bench --simple 1 2 3

echo
echo "4 elementos"
$PS --bench --simple 4 3 2 1
$PS --bench --simple 2 4 1 3
$PS --bench --simple 3 1 4 2

echo
echo "5 elementos"
$PS --bench --simple 5 4 3 2 1
$PS --bench --simple 2 5 1 4 3
$PS --bench --simple 4 2 5 3 1

echo
echo "=============================="
echo "TESTES DE ERRO"
echo "=============================="

$PS 1 1
$PS a
$PS 2147483648
$PS -2147483649
$PS ++1
$PS 12a

echo
echo "=============================="
echo "TESTES ADAPTATIVE"
echo "=============================="

$PS --bench 3 2 1
$PS --bench 5 4 3 2 1

echo
echo "=============================="
echo "TESTES ALEATÓRIOS"
echo "=============================="

for i in {1..10}
do
    ARG=$(shuf -i 1-20 -n 20)
    echo
    echo "Teste $i"
    echo "$ARG"
    $PS --bench $ARG
done

echo
echo "Fim dos testes."