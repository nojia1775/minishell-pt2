/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:11:59 by nadjemia          #+#    #+#             */
/*   Updated: 2024/05/11 10:52:37 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	conform_pipe(char *str)
{
	int	i;
	int	charac;
	int	in_single;
	int	in_double;
	
	i = -1;
	charac = 0;
	in_single = 0;
	in_double = 0;
	while (str[++i])
	{
		if (str[i] == 34 && !in_single)
			in_double = (in_double + 1) % 2;
		if (str[i] == 39 && !in_double)
			in_single = (in_single + 1) % 2;
		if (ft_isalnum(str[i]))
			charac = 1;
		if (str[i] == '|' && !charac && !in_single && !in_double)
			return (0);
		else if (str[i] == '|' && str[i + 1] == '|')
			return (0);
		else if (str[i] == '|' && (!in_double || !in_single))
			charac = 0;
	}
	if (!charac)
		return (0);
	return (1);
}

int	count_pipe(char *str)
{
	int	i;
	int	count;
	int	in_single;
	int	in_double;
	
	in_single = 0;
	in_double = 0;
	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 && !in_single)
			in_double = (in_double + 1) % 2;
		if (str[i] == 39 && !in_double)
			in_single = (in_single + 1) % 2;
		if (str[i] == '|' && !in_double && !in_single)
			count++;
	}
	return (count);
}