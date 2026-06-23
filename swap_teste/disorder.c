/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 15:14:11 by username          #+#    #+#             */
/*   Updated: 2026/06/22 21:16:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double	disorder(t_stack *stack)
{
	double	mistakes;
	double	total;
	t_node	*outer;
	t_node	*inner;

	if (total == 0)
		return (0.0);
	mistakes = 0;
	total = 0;
	outer = stack->head;

	while (outer != NULL && outer->next != NULL)
	{
		inner = outer->next;

		while (inner != NULL)
		{
			total += 1;
			if (outer->data > inner->data)
			{
				mistakes += 1;
			}
			inner = inner->next;
		}
		outer = outer->next;			
	}
	return (mistakes / total);
}
