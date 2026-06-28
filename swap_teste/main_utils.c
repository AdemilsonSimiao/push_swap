/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc2 <pc2@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 08:47:23 by pc2               #+#    #+#             */
/*   Updated: 2026/06/27 08:49:03 by pc2              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack *select_and_sort(t_stack *a, t_stack *b, t_options *opt)
{

	if(opt->mode == SIMPLE)
		sort_n2(a, b, opt);
	else if(opt->mode == MEDIUM)
		sort_chunk(a, b, opt);
	else if(opt->mode == COMPLEX)
		sort_radix(a, b, opt);
	else if(opt->mode == ADAPTIVE)
		sort_adaptative(a, b, opt);
	return(a);
}

void print_bench(t_options *opt)
{
	int total;
	int part1;
	int part2;
	char *str;
	char *msg;

	total = opt->disorder_value * 10000 + 0.5;
	part1 = total / 100;
	part2 = total % 100;
	str = ft_itoa(part1);
	write(2, "[bench] disorder: ", 18);
	write(2, str, ft_strlen(str));
	write(2, ".", 1);
	free(str);
	str = ft_itoa(part2);
	write(2, str, ft_strlen(str));
	write(2, "%\n", 2);
	free(str);
	if(opt->mode == SIMPLE)
	msg = "[bench] strategy: Simple /O(n^2)\n";
	else if(opt->mode == MEDIUM)
	msg = "[bench] strategy: Medium /O(n*sqrt(n))\n";
	else if(opt->mode == COMPLEX)
	msg = "[bench] strategy: Complex /O(n log n)\n";
	else 
		msg = "[bench] strategy: Adaptive /O(n*sqrt(n))\n";
	write(2, msg, ft_strlen(msg));
	print_total_ops(opt);
	print_opt_counts(opt);
	print_opt_counts2(opt);
}

void print_total_ops(t_options *opt)
{
	int total_opt;
	int i;
	char *str;

	i = 0;
	total_opt = 0;
	
	while(i < 11)
	{
		total_opt += opt->counts[i];
		i++;
	}
	str = ft_itoa(total_opt);
	write(2, "[bench] total_ops: ", ft_strlen("[bench] total_ops: "));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	free(str);
}

void print_opt_counts(t_options *opt)
{
	char *str;

	write(2, "[bench] sa: ", ft_strlen("[bench] sa: "));
	str = ft_itoa(opt->counts[SA]);
	write(2, str, ft_strlen(str));
	free(str);
	write(2, " sb: ", ft_strlen(" sb: "));
	str = ft_itoa(opt->counts[SB]);
	write(2, str, ft_strlen(str));
	free(str);
	write(2, " ss: ", ft_strlen(" ss: "));
	str = ft_itoa(opt->counts[SS]);
	write(2, str, ft_strlen(str));
	free(str);
	write(2, " pa: ", ft_strlen(" pa: "));
	str = ft_itoa(opt->counts[PA]);
	write(2, str, ft_strlen(str));
	free(str);
	write(2, " pb: ", ft_strlen(" pb: "));
	str = ft_itoa(opt->counts[PB]);
	write(2, str, ft_strlen(str));
	free(str);
	write(2, "\n", 1);
}

void	print_opt_counts2(t_options *opt)
{
	char *str;

	write(2, "[bench] ra: ", ft_strlen("[bench] ra: "));
	str = ft_itoa(opt->counts[RA]);
	write(2, str, ft_strlen(str));
	free(str);
	write(2, " rb: ", ft_strlen(" rb: "));
	str = ft_itoa(opt->counts[RB]);
	write(2, str, ft_strlen(str));
	free(str);
	write(2, " rr: ", ft_strlen(" rr: "));
	str = ft_itoa(opt->counts[RR]);
	write(2, str, ft_strlen(str));
	free(str);
	write(2, " rra: ", ft_strlen(" rra: "));
	str = ft_itoa(opt->counts[RRA]);
	write(2, str, ft_strlen(str));
	free(str);
	write(2, " rrb: ", ft_strlen(" rrb: "));
	str = ft_itoa(opt->counts[RRB]);
	write(2, str, ft_strlen(str));
	free(str);
	write(2, " rrr: ", ft_strlen(" rrr: "));
	str = ft_itoa(opt->counts[RRR]);
	write(2, str, ft_strlen(str));
	free(str);
	write(2, "\n", 1);
}
