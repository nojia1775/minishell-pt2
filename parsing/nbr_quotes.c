/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:50:25 by codespace         #+#    #+#             */
/*   Updated: 2024/08/29 12:17:34 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	in_or_not(char c, int *in_double, int *in_single)
{
	if (c == 34 && !(*in_double) && !(*in_single))
		*in_double = 1;
	else if (c == 34 && *in_double && !(*in_single))
		*in_double = 0;
	if (c == 39 && !(*in_single) && !(*in_double))
		*in_single = 1;
	else if (c == 39 && *in_single && !(*in_double))
		*in_single = 0;
}

int	nbr_quotes(char *str)
{
	int	i;
	int	sgl;
	int	dbl;
	int	in_double;
	int	in_single;

	in_double = 0;
	in_single = 0;
	sgl = 0;
	dbl = 0;
	i = -1;
	while (str[++i])
	{
		in_or_not(str[i], &in_double, &in_single);
		if (str[i] == 34 && !in_single)
			dbl++;
		if (str[i] == 39 && !in_double)
			sgl++;
	}
	if (sgl % 2 || dbl % 2)
		return (0);
	return (1);
}
