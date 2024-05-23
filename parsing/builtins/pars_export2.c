/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_export2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:12:36 by almichel          #+#    #+#             */
/*   Updated: 2024/05/22 02:04:55 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	checking_nbr_quotes(char *str)
{
	int	i;
	int	count;
	int	count2;

	count2 = 0;
	count = 0;
	i = 0;

	while (str[i])
	{
		if (str[i] == '"')
			count++;
		else if (str[i] == '\'')
			count2++;
		i++;
	}
	if (count % 2 == 0 && count2 == 0)
		return (1);
	else if (count2 % 2 == 0 && count == 0)
		return (1);
	else if (count2 % 2 == 0 && count % 2 == 0)
		return (1);
	return (-1);
}
