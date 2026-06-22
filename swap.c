#include "push_swap.h"
void swap(t_stack *stack)
{
	int tmp;
	tmp = stack->data;
	stack->data = t_tmp_stack->a;
	t_tmp_stack->a = tmp;
}