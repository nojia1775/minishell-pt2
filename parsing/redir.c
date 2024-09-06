/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:09:49 by nadjemia          #+#    #+#             */
/*   Updated: 2024/09/06 17:48:40 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	conform_redir(char *str)
{
	int	i;
	int	in_double;
	int	in_single;

	in_single = 0;
	in_double = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 && !in_single)
			in_double = (in_double + 1) % 2;
		if (str[i] == 39 && !in_double)
			in_single = (in_single + 1) % 2;
		if (str[i] == '>')
		{
			if (str[i + 1] == '>' && str[i + 2] == '>')
				return (0);
		}
	}
	return (1);
}
