/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc2 <pc2@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 15:05:06 by username          #+#    #+#             */
/*   Updated: 2026/06/27 14:58:40 by pc2              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
# include "./libft/libft.h"
int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	t_options	opt;
	
	ft_bzero(&opt, sizeof(t_options));
	
	if (argc < 2)
		return (0);
	stack_b = ft_new_stack();
	if(parse_options(argc, argv, &opt) == -1)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	stack_a = ft_parse_args(argv, opt.start_index);
	printf("----------\n");

	t_node *tmp = stack_a->head;

	while (tmp)
	{
		printf("%d\n", tmp->data);
		tmp = tmp->next;
	}

	printf("----------\n");
	if(!stack_a)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	opt.disorder_value = disorder(stack_a);
	stack_a = select_and_sort(stack_a, stack_b, &opt);
	if (!stack_a)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if(opt.bench == 1)
		print_bench(&opt);
	return (0);
}
