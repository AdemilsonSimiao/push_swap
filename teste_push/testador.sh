#!/bin/bash

# Cores para o output do terminal
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
RESET='\033[0m'

echo "============================================="
echo "      INICIANDO VALIDAÇÃO DO ECOSSISTEMA      "
echo "============================================="

# 1. Compilar push_swap
gcc -Wall -Wextra -Werror push_swap.c -o push_swap 2>/dev/null
if [ $? -eq 0 ]; then
    echo -e "Compilação push_swap: ${GREEN}[OK]${RESET}"
else
    echo -e "Compilação push_swap: ${RED}[FALHOU]${RESET}"
    exit 1
fi

# 2. Compilar checker
gcc -Wall -Wextra -Werror checker.c -o checker 2>/dev/null
if [ $? -eq 0 ]; then
    echo -e "Compilação checker:   ${GREEN}[OK]${RESET}"
else
    echo -e "Compilação checker:   ${RED}[FALHOU]${RESET}"
    exit 1
fi

echo "============================================="

# Teste 1: Lista de 3 Números (Limite Escolar: 3 ops)
ARG_3=$(seq -100 100 | shuf -n 3 | tr '\n' ' ')
OPS_3=$(./push_swap $ARG_3 | wc -l)
CHECK_3=$(./push_swap $ARG_3 | ./checker $ARG_3)

echo "Teste com 3 números: $ARG_3"
echo "-> Operações: $OPS_3 (Meta: <= 3)"
if [ "$CHECK_3" = "OK" ] && [ $OPS_3 -le 3 ]; then
    echo -e "-> Resultado: ${GREEN}[PASSOU - OK]${RESET}"
else
    echo -e "-> Resultado: ${RED}[FALHOU - KO ou Limpe Estourado]${RESET} (Checker deu: $CHECK_3)"
fi

echo "============================================="

# Teste 2: Lista de 5 Números (Limite Escolar: 12 ops)
ARG_5=$(seq -100 100 | shuf -n 5 | tr '\n' ' ')
OPS_5=$(./push_swap $ARG_5 | wc -l)
CHECK_5=$(./push_swap $ARG_5 | ./checker $ARG_5)

echo "Teste com 5 números: $ARG_5"
echo "-> Operações: $OPS_5 (Meta: <= 12)"
if [ "$CHECK_5" = "OK" ] && [ $OPS_5 -le 12 ]; then
    echo -e "-> Resultado: ${GREEN}[PASSOU - OK]${RESET}"
else
    echo -e "-> Resultado: ${RED}[FALHOU - KO ou Limpe Estourado]${RESET} (Checker deu: $CHECK_5)"
fi

echo "============================================="

# Teste 3: Modo Médio (100 Números) - Nota Máxima se <= 700 ops
ARG_100=$(seq -500 500 | shuf -n 100 | tr '\n' ' ')
OPS_100=$(./push_swap $ARG_100 | wc -l)
CHECK_100=$(./push_swap $ARG_100 | ./checker $ARG_100)

echo "Teste com 100 números aleatórios..."
echo "-> Operações: $OPS_100 (Meta Nota Máxima: <= 700)"
if [ "$CHECK_100" = "OK" ]; then
    if [ $OPS_100 -le 700 ]; then 
        echo -e "-> Resultado: ${GREEN}[EXCELENTE - OK] Nota Máxima (5/5 pts)!${RESET}"
    elif [ $OPS_100 -le 1500 ]; then
        echo -e "-> Resultado: ${YELLOW}[PASSOU - OK] Eficiência Regular (Aprovado).${RESET}"
    else
        echo -e "-> Resultado: ${RED}[FALHOU - OK mas Estourou Movimentos] Max 1500!${RESET}"
    fi
else
    echo -e "-> Resultado: ${RED}[CRÍTICO - KO] A lista terminou DESORDENADA!${RESET}"
fi

echo "============================================="

# Teste 4: Modo Complexo (500 Números) - Aprovação se <= 5500 ops
ARG_500=$(seq -1000 1000 | shuf -n 500 | tr '\n' ' ')
OPS_500=$(./push_swap $ARG_500 | wc -l)
CHECK_500=$(./push_swap $ARG_500 | ./checker $ARG_500)

echo "Teste com 500 números aleatórios..."
echo "-> Operações: $OPS_500 (Meta Mínima: <= 5500)"
if [ "$CHECK_500" = "OK" ] && [ $OPS_500 -le 5500 ]; then
    echo -e "-> Resultado: ${GREEN}[PASSOU - OK] Sistema robusto para grandes volumes!${RESET}"
else
    echo -e "-> Resultado: ${RED}[FALHOU] Lista corrompida ou acima de 5500 ops (Checker: $CHECK_500)${RESET}"
fi
echo "============================================="
