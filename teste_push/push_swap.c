#include <unistd.h>
#include <stdlib.h>

/* --- ESTRUTURAS DE DADOS --- */
typedef struct s_node {
    int             value;
    int             index;
    struct s_node   *next;
} t_node;

typedef struct s_env {
    int     bench;
    int     force_mode; // 1: Simple, 2: Medium, 3: Complex, 4: Adaptive
    long    op_count;
} t_env;

/* Global para rastreamento de ambiente e benchmark (evita modificar assinaturas de funções escolares) */
t_env g_env = {0, 0, 0};

/* --- AUXILIARES DE TEXTO E ERRO --- */
void ft_putstr(char *str) {
    while (*str) write(1, str++, 1);
}

void ft_putnbr(long n) {
    if (n < 0) {
        write(1, "-", 1);
        n = -n;
    }
    if (n >= 10) ft_putnbr(n / 10);
    char c = (n % 10) + '0';
    write(1, &c, 1);
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

int stack_size(t_node *stack) {
    int size = 0;
    while (stack) { size++; stack = stack->next; }
    return (size);
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
        if ((sign * num) > 2147483647 || (sign * num) < -2147483648) ft_error(stack_a, NULL);
        i++;
    }
    return (num * sign);
}

/* --- OPERAÇÕES DISPONÍVEIS (SEÇÃO 6) --- */
void track_op(char *op) {
    g_env.op_count++;
    ft_putstr(op);
}

void sa(t_node **stack_a, int print) {
    if (!*stack_a || !(*stack_a)->next) return;
    t_node *first = *stack_a; t_node *second = first->next;
    first->next = second->next; second->next = first; *stack_a = second;
    if (print) track_op("sa\n");
}

void sb(t_node **stack_b, int print) {
    if (!*stack_b || !(*stack_b)->next) return;
    t_node *first = *stack_b; t_node *second = first->next;
    first->next = second->next; second->next = first; *stack_b = second;
    if (print) track_op("sb\n");
}

void pa(t_node **stack_a, t_node **stack_b) {
    if (!*stack_b) return;
    t_node *tmp = *stack_b; *stack_b = (*stack_b)->next;
    tmp->next = *stack_a; *stack_a = tmp;
    track_op("pa\n");
}

void pb(t_node **stack_a, t_node **stack_b) {
    if (!*stack_a) return;
    t_node *tmp = *stack_a; *stack_a = (*stack_a)->next;
    tmp->next = *stack_b; *stack_b = tmp;
    track_op("pb\n");
}

void ra(t_node **stack_a, int print) {
    if (!*stack_a || !(*stack_a)->next) return;
    t_node *first = *stack_a; t_node *last = *stack_a;
    while (last->next) last = last->next;
    *stack_a = first->next; first->next = NULL; last->next = first;
    if (print) track_op("ra\n");
}

void rb(t_node **stack_b, int print) {
    if (!*stack_b || !(*stack_b)->next) return;
    t_node *first = *stack_b; t_node *last = *stack_b;
    while (last->next) last = last->next;
    *stack_b = first->next; first->next = NULL; last->next = first;
    if (print) track_op("rb\n");
}

void rra(t_node **stack_a, int print) {
    if (!*stack_a || !(*stack_a)->next) return;
    t_node *last = *stack_a; t_node *prev = NULL;
    while (last->next) { prev = last; last = last->next; }
    prev->next = NULL; last->next = *stack_a; *stack_a = last;
    if (print) track_op("rra\n");
}

void rrb(t_node **stack_b, int print) {
    if (!*stack_b || !(*stack_b)->next) return;
    t_node *last = *stack_b; t_node *prev = NULL;
    while (last->next) { prev = last; last = last->next; }
    prev->next = NULL; last->next = *stack_b; *stack_b = last;
    if (print) track_op("rrb\n");
}

/* --- VALIDAÇÃO E COORDENAÇÃO (SEÇÃO 2 & 3) --- */
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
    new_node->value = value; new_node->index = -1; new_node->next = NULL;
    if (!*stack) { *stack = new_node; return; }
    t_node *tmp = *stack;
    while (tmp->next) tmp = tmp->next;
    tmp->next = new_node;
}

int is_sorted(t_node *stack) {
    while (stack && stack->next) {
        if (stack->value > stack->next->value) return (0);
        stack = stack->next;
    }
    return (1);
}

void index_stack(t_node *stack) {
    t_node *ptr; t_node *min_node;
    int size = stack_size(stack);
    for (int i = 0; i < size; i++) {
        ptr = stack; min_node = NULL;
        while (ptr) {
            if (ptr->index == -1 && (!min_node || ptr->value < min_node->value)) min_node = ptr;
            ptr = ptr->next;
        }
        if (min_node) min_node->index = i;
    }
}

/* --- CALCULADOR DE DESORDEM (SEÇÃO 3) --- */
int calculate_disorder(t_node *stack) {
    int size = stack_size(stack);
    if (size <= 1) return 0;
    int *arr = malloc(sizeof(int) * size);
    t_node *tmp = stack;
    for (int i = 0; i < size; i++) { arr[i] = tmp->value; tmp = tmp->next; }
    
    int inversions = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) inversions++;
        }
    }
    free(arr);
    int max_inversions = (size * (size - 1)) / 2;
    if (max_inversions == 0) return 0;
    return (inversions * 100) / max_inversions;
}

/* --- 5A. MODO SIMPLE (SORT_N2) --- */
void sort_three(t_node **stack_a) {
    int first = (*stack_a)->value; int second = (*stack_a)->next->value; int third = (*stack_a)->next->next->value;
    if (first > second && second < third && first < third) sa(stack_a, 1);
    else if (first > second && second > third) { sa(stack_a, 1); rra(stack_a, 1); }
    else if (first > second && second < third && first > third) ra(stack_a, 1);
    else if (first < second && second > third && first < third) { sa(stack_a, 1); ra(stack_a, 1); }
    else if (first < second && second > third && first > third) rra(stack_a, 1);
}

void sort_n2(t_node **stack_a, t_node **stack_b) {
    int size = stack_size(*stack_a);
    if (size == 2) { sa(stack_a, 1); return; }
    if (size == 3) { sort_three(stack_a); return; }
    while (stack_size(*stack_a) > 3) {
        t_node *tmp = *stack_a; int min_idx = tmp->index;
        while (tmp) { if (tmp->index < min_idx) min_idx = tmp->index; tmp = tmp->next; }
        while ((*stack_a)->index != min_idx) ra(stack_a, 1);
        pb(stack_a, stack_b);
    }
    sort_three(stack_a);
    while (*stack_b) pa(stack_a, stack_b);
}

/* --- 5B. MODO MEDIUM (SORT_CHUNK) --- */
void sort_chunk(t_node **stack_a, t_node **stack_b) {
    int size = stack_size(*stack_a);
    int chunks = (size <= 50) ? 2 : 4;
    int chunk_size = size / chunks;
    
    for (int i = 0; i < chunks; i++) {
        int max_chunk_idx = (i == chunks - 1) ? size : (i + 1) * chunk_size;
        int current_chunk_elements = max_chunk_idx - (i * chunk_size);
        int pushed = 0;
        
        while (pushed < current_chunk_elements && stack_size(*stack_a) > 0) {
            if ((*stack_a)->index < max_chunk_idx) {
                pb(stack_a, stack_b);
                pushed++;
            } else {
                ra(stack_a, 1);
            }
        }
    }
    while (*stack_b) {
        t_node *tmp = *stack_b; int max_idx = tmp->index;
        while (tmp) { if (tmp->index > max_idx) max_idx = tmp->index; tmp = tmp->next; }
        while ((*stack_b)->index != max_idx) rb(stack_b, 1);
        pa(stack_a, stack_b);
    }
}

/* --- 5C. MODO COMPLEX (SORT_RADIX) --- */
void sort_radix(t_node **stack_a, t_node **stack_b) {
    int size = stack_size(*stack_a); int max_bits = 0;
    while (((size - 1) >> max_bits) != 0) max_bits++;
    for (int i = 0; i < max_bits; i++) {
        for (int j = 0; j < size; j++) {
            if ((((*stack_a)->index >> i) & 1) == 1) ra(stack_a, 1);
            else pb(stack_a, stack_b);
        }
        while (*stack_b) pa(stack_a, stack_b);
    }
}

/* --- CONTROLADOR DE ESTRATÉGIA (SEÇÃO 4) --- */
void execute_strategy(t_node **stack_a, t_node **stack_b) {
    int size = stack_size(*stack_a);
    int disorder = calculate_disorder(*stack_a);
    int selected_mode = g_env.force_mode;

    if (selected_mode == 4 || selected_mode == 0) { // Adaptativo ou Automático
        if (selected_mode == 4) {
            if (disorder < 20) selected_mode = 1;      // Baixa Desordem -> Simple
            else if (disorder <= 50) selected_mode = 2; // Média Desordem -> Chunk
            else selected_mode = 3;                    // Alta Desordem -> Radix
        } else {
            if (size <= 5) selected_mode = 1;
            else if (size <= 100) selected_mode = 2;
            else selected_mode = 3;
        }
    }

    if (selected_mode == 1) sort_n2(stack_a, stack_b);
    else if (selected_mode == 2) sort_chunk(stack_a, stack_b);
    else if (selected_mode == 3) sort_radix(stack_a, stack_b);
}

/* --- MAIN & PARSE_OPTIONS (SEÇÃO 1 & 2) --- */
int main(int argc, char **argv)
{
    t_node *stack_a = NULL; t_node *stack_b = NULL;
    int arg_start = 1;
    if (argc < 2) return (0);

    /* 1. PARSE_OPTIONS */
    while (arg_start < argc && argv[arg_start][0] == '-' && argv[arg_start][1] == '-')
	{
        if (ft_strcmp(argv[arg_start], "--bench") == 0) g_env.bench = 1;
        else if (ft_strcmp(argv[arg_start], "--simple") == 0) g_env.force_mode = 1;
		else if (ft_strcmp(argv[arg_start], "--medium") == 0) g_env.force_mode = 2;
		else if (ft_strcmp(argv[arg_start], "--complex") == 0) g_env.force_mode = 3;
		else if (ft_strcmp(argv[arg_start], "--adaptive") == 0)	g_env.force_mode = 4;
		else 
			write(2, "Error\n", 6), exit(1);
		arg_start++;
	}
	if (arg_start >= argc)
		return (0);
	/* 2. FT_PARSE_ARGS & CONVERSÃO */
	volatile unsigned long start_timer = 0; 
	// Aproximação de clock interno para simular tempo
	for (int i = arg_start; i < argc; i++)
	{
		long val = ft_atoi(argv[i], &stack_a);
		add_back(&stack_a, (int)val);
		start_timer += 50;
	}
	check_duplicates(stack_a);
	if (is_sorted(stack_a))
	{
		free_stack(&stack_a); 
		return (0);
	}
	/* 3. INDEXAÇÃO */
	index_stack(stack_a);
	/* 4. EXECUÇÃO DO ALGORITMO */
	execute_strategy(&stack_a, &stack_b);
	/* 6. EXIBIÇÃO DO BENCHMARK */
	if (g_env.bench)
	{
		ft_putstr("\n=== BENCHMARK REPORT ===\n");
		ft_putstr("Total Operations: ");
		ft_putnbr(g_env.op_count);
		ft_putstr("\nInitial Disorder: ");
		ft_putnbr(calculate_disorder(stack_a));
		// Mostra o valor calculado originalmente antes de limpar
		ft_putstr("%\n========================\n");
	}

	/* 7. FINALIZAÇÃO (FIM) */
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}