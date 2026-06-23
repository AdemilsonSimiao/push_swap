/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 02:19:10 by codespace         #+#    #+#             */
/*   Updated: 2026/06/23 02:19:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int get_chunk_size(int total_size)
{
	int i;

	i = 1;
	while (i * i < total_size)
		i++;
	return (i);
}

int index_pos(t_stack *stack, int target)
{
	t_node *curr;
	int pos;
	if (!stack || !stack->head)
		return (-1);
	curr = stack->head;
	pos = 0;

	while (curr)
	{
		if (curr->index == target)
			return (pos);
		pos++;
		curr = curr->next;
	}
	return (-1);
}

void move_top(t_stack *stack, int target)
{
	int pos;

	pos = index_pos(stack, target);
	if (pos == - 1)
		return ;
	if (pos <= stack->size / 2)
	{
		while (pos--)
			ra(stack);
	}
	else
	{
		pos = stack->size - pos;
		while (pos--)
			rra(stack);
	}
}

void push_chunk(t_stack *a, t_stack *b, int chunk_size, int start)
{
	int i;
	
	i = 0;
	while (i < chunk_size && a->size > 0)
	{
		if ((a->head->index >= start) && (a->head->index < start + chunk_size))
		{
			pb(a, b);
			if (b->size > 1)
				rb(b);
			i++;
		}
		else
			ra(a);
	}
}

void sort_chunk(t_stack *a, t_stack *b)
{
	int chunk_size;
	int chunks;
	int i;
	int max_index;

	max_index = a->size - 1;
	chunk_size = get_chunk_size(a->size);
	chunks = (a->size + chunk_size - 1) / chunk_size;
	i = 0;
	
	while (i < chunks && a->size > 0)
	{
		push_chunk(a, b, chunk_size, i * chunk_size);
		i ++;
	}
	i = max_index;
	while (b->size > 0)
	{
		move_top(b, i);
		pa(a, b);
		i--;
	}
}
