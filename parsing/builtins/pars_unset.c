/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 02:08:02 by almichel          #+#    #+#             */
/*   Updated: 2024/06/13 18:47:59 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pars_unset(char *str)
{
	char **unset;
	int		i;

	i = 1;
	unset = ft_split(str, ' ');
	if (!unset[1])
	{
		return;
	}
	else 
		{
			while (unset[i])
			{
				unset[i] = pars_unset_var(unset[i]);
				i++;
			}
		}
	free_double_tabs(unset);
}

char	*pars_unset_var(char *str)
{
	// if (checking_nbr_quotes(str) == -1)
	// {
	// 	ft_putstr_msg(": not a valid identifier\n", 2, str);
	// 	return (str);
	// }
	if (checking_order_quotes(str) == -1)
	{
		str = del_outside_quotes(str);
		return (str);
	}
	else if (checking_order_quotes(str) == 1)
	{
		str = del_all_quotes(str);
		return (str);
	}
	return (str);
}
