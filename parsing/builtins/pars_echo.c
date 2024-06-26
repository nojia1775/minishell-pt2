/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:05:49 by almichel          #+#    #+#             */
/*   Updated: 2024/05/25 02:19:15 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_option_echo(char *str, int *n_option)
{
	int	i;

	i = 0;
	*n_option = 0;
	
	if (str[0] != '-' || str[i] != 'n')
	{
		*n_option = -1;
		return;
	}
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
		{
			*n_option = -1;
			return;
		}
		i++;
	}
	return;
}
