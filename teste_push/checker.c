#include <unistd.h>
#include <stdlib.h>

/* --- 1. ESTRUTURA DE DADOS --- */
typedef struct s_node {
    int             value;
    struct s_node   *next;
} t_node;

/* --- 2. AUXILIARES DE TEXTO E ERRO --- */
void ft_putstr(char *str) {
    while (*str)
        write(1, str++, 1);
}

void free_stack(t_node **stack) {
    t_node *tmp;
    if (!stack || !*stack) return;
    while (*stack) {
        tmp = (*stack)->next;
        free(*stack);
        *stack = tmp;
    }
}

void ft_error(t_node **stack_a, t_node **stack_b) {
    free_stack(stack_a);
    free_stack(stack_b);
    write(2, "Error\n", 6);
    exit(1);
}

int ft_strcmp(char *s1, char *s2) {
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i]) i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

long ft_atoi(char *str, t_node **stack_a) {
    long num = 0; int sign = 1; int i = 0;
    if (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-') sign = -1;
        i++;
    }
    if (!str[i]) ft_error(stack_a, NULL);
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9') ft_error(stack_a, NULL);
        num = num * 10 + (str[i] - '0');
        if ((sign * num) > 2147483647 || (sign * num) < -2147483648)
            ft_error(stack_a, NULL);
        i++;
    }
    return (num * sign);
}

/* --- 3. OPERAÇÕES REAIS (SEM EXIBIR OUTPUT) --- */
void sa(t_node **stack_a) {
    if (!*stack_a || !(*stack_a)->next) return;
    t_node *first = *stack_a; t_node *second = first->next;
    first->next = second->next; second->next = first; *stack_a = second;
}

void sb(t_node **stack_b) {
    if (!*stack_b || !(*stack_b)->next) return;
    t_node *first = *stack_b; t_node *second = first->next;
    first->next = second->next; second->next = first; *stack_b = second;
}

void ss(t_node **stack_a, t_node **stack_b) {
    sa(stack_a); sb(stack_b);
}

void pa(t_node **stack_a, t_node **stack_b) {
    if (!*stack_b) return;
    t_node *tmp = *stack_b; *stack_b = (*stack_b)->next;
    tmp->next = *stack_a; *stack_a = tmp;
}

void pb(t_node **stack_a, t_node **stack_b) {
    if (!*stack_a) return;
    t_node *tmp = *stack_a; *stack_a = (*stack_a)->next;
    tmp->next = *stack_b; *stack_b = tmp;
}

void ra(t_node **stack_a) {
    if (!*stack_a || !(*stack_a)->next) return;
    t_node *first = *stack_a; t_node *last = *stack_a;
    while (last->next) last = last->next;
    *stack_a = first->next; first->next = NULL; last->next = first;
}

void rb(t_node **stack_b) {
    if (!*stack_b || !(*stack_b)->next) return;
    t_node *first = *stack_b; t_node *last = *stack_b;
    while (last->next) last = last->next;
    *stack_b = first->next; first->next = NULL; last->next = first;
}

void rr(t_node **stack_a, t_node **stack_b) {
    ra(stack_a); rb(stack_b);
}

void rra(t_node **stack_a) {
    if (!*stack_a || !(*stack_a)->next) return;
    t_node *last = *stack_a; t_node *prev = NULL;
    while (last->next) { prev = last; last = last->next; }
    prev->next = NULL; last->next = *stack_a; *stack_a = last;
}

void rrb(t_node **stack_b) {
    if (!*stack_b || !(*stack_b)->next) return;
    t_node *last = *stack_b; t_node *prev = NULL;
    while (last->next) { prev = last; last = last->next; }
    prev->next = NULL; last->next = *stack_b; *stack_b = last;
}

void rrr(t_node **stack_a, t_node **stack_b) {
    rra(stack_a); rrb(stack_b);
}

/* --- 4. EXECUÇÃO DE COMANDOS LIDOS --- */
void parse_and_execute(char *line, t_node **stack_a, t_node **stack_b) {
    if (ft_strcmp(line, "sa\n") == 0) sa(stack_a);
    else if (ft_strcmp(line, "sb\n") == 0) sb(stack_b);
    else if (ft_strcmp(line, "ss\n") == 0) ss(stack_a, stack_b);
    else if (ft_strcmp(line, "pa\n") == 0) pa(stack_a, stack_b);
    else if (ft_strcmp(line, "pb\n") == 0) pb(stack_a, stack_b);
    else if (ft_strcmp(line, "ra\n") == 0) ra(stack_a);
    else if (ft_strcmp(line, "rb\n") == 0) rb(stack_b);
    else if (ft_strcmp(line, "rr\n") == 0) rr(stack_a, stack_b);
    else if (ft_strcmp(line, "rra\n") == 0) rra(stack_a);
    else if (ft_strcmp(line, "rrb\n") == 0) rrb(stack_b);
    else if (ft_strcmp(line, "rrr\n") == 0) rrr(stack_a, stack_b);
    else ft_error(stack_a, stack_b);
}

/* --- 5. PARSE E VALIDAÇÃO DA ENTRADA --- */
void check_duplicates(t_node *stack) {
    t_node *tmp;
    while (stack) {
        tmp = stack->next;
        while (tmp) {
            if (stack->value == tmp->value) ft_error(&stack, NULL);
            tmp = tmp->next;
        }
        stack = stack->next;
    }
}

void add_back(t_node **stack, int value) {
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node) ft_error(stack, NULL);
    new_node->value = value; new_node->next = NULL;
    if (!*stack) { *stack = new_node; return; }
    t_node *tmp = *stack;
    while (tmp->next) tmp = tmp->next;
    tmp->next = new_node;
}

int is_sorted(t_node *stack) {
    if (!stack) return (1);
    while (stack && stack->next) {
        if (stack->value > stack->next->value) return (0);
        stack = stack->next;
    }
    return (1);
}

/* Mini Get_Next_Line estático via sys_read caractere por caractere */
int get_line(char *buffer) {
    int i = 0; char c; int bytes;
    while ((bytes = read(0, &c, 1)) > 0) {
        buffer[i++] = c;
        if (c == '\n' || i >= 9) break;
    }
    buffer[i] = '\0';
    return (bytes);
}

/* --- 6. CONTROLADOR CENTRAL DO CHECKER --- */
int main(int argc, char **argv) {
    t_node *stack_a = NULL; t_node *stack_b = NULL;
    char buffer[10];

    if (argc < 2) return (0);

    for (int i = 1; i < argc; i++) {
        long val = ft_atoi(argv[i], &stack_a);
        add_back(&stack_a, (int)val);
    }
    check_duplicates(stack_a);

    /* Loop de leitura da Stdin */
    while (get_line(buffer) > 0) {
        parse_and_execute(buffer, &stack_a, &stack_b);
    }

    /* Validação Final do Resultado */
    if (is_sorted(stack_a) && stack_b == NULL)
        ft_putstr("OK\n");
    else
        ft_putstr("KO\n");

    free_stack(&stack_a);
    free_stack(&stack_b);
    return (0);
}
