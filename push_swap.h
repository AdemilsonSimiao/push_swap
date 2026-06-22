#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
typedef struct s_stack
{
	int *data;
	int size;
}t_stack;
typedef struct s_tmp_stack
{
	t_stack a;
	t_stack b;
}t_tmp_stack;

int parse_input(int argc, char **argv, t_stack *a);
int is_sorted(t_stack *stack);
void swap(t_stack *stack);
void push(t_stack *src, t_stack *dst);
void rotate(t_stack *stack);
void reverse_rotate(t_stack *stack);
void solve(t_tmp_stack *tmp_stack);
int ft_isspace(int c);
int ft_isdigit(int c);

#endif