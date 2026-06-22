#include "push_swap.h"

// parse_input: converte argv em uma pilha A válida
int parse_input(int argc, char **argv, t_stack *a)
{
    // verificar se argc >= 2, caso contrário não há números
    if (argc >= 2)
        return (0);
    // contar quantos valores existem em argv
    //   para cada argumento:
    //     se o argumento contiver espaços, separar os tokens
    //     caso contrário, contar como um token
    // alocar a->data com tamanho igual ao número total de valores
    // se a alocação falhar, retornar erro

    // índice de escrita em a->data começa em zero
    // para cada argumento em argv:
    //   separar o argumento em tokens se necessário
    //   para cada token:
    //     validar o token como número
    //       verificar sinal +/-
    //       verificar dígitos
    //       converter para int sem overflow
    //     se inválido, liberar memória e retornar erro
    //     armazenar o valor convertido em a->data[pos]
    //     incrementar pos

    // após preencher a->data, definir a->size = total de valores

    // verificar duplicatas em a->data
    //   comparar cada elemento com os demais
    //   se encontrar duplicata, liberar memória e retornar erro

    // sucesso: retornar 1 ou valor booleano apropriado
}

// helper: conta valores totais em argv
int count_values(int argc, char **argv)
{
    // inicializar contador em zero
    int i;
    int j;
    int token;
    int total;

    total = 0;
    i = 1;
    // para cada argumento:
    while (i < argc)
    {
       j = 0;
       token = 0;
       while (argv[i][j])
       {
        if  (ft_isspace(argv[i][j]) == 0)
            token = 0;
        else if (!token)
        {
            total++;
            token = 1;
        }
        j++;
       }
       i++;
    }
    
    return (total);
}

// helper: checa se um token é um inteiro válido
int is_valid_number(const char *token)
{
    int i;
    long value;
    // permitir opcionalmente '+' ou '-' no início
    if (!token || token[0] == '\0')
        return (0);
    i = 0;
    if (token[i] == '+' || token[i] == '-')
        i++;
    // exigir pelo menos um dígito
    if (token[i] == '\0')
        return (0);
    // garantir que todos os outros caracteres são dígitos
    while (token[i])
    {
        if (ft_isdigit(token[i]) == 0)
            return (0);
        i++;
    }
    
    // converter com cuidado para int
    // verificar overflow/underflow
    // retornar true se válido, false se inválido
}

// helper: detecta duplicatas
int has_duplicates(int *data, int size)
{
    // para cada elemento i:
    //   comparar com todos os elementos j > i
    //   se encontrar iguais, retornar true
    // retornar false se não houver duplicatas
}