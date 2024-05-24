/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 02:08:02 by almichel          #+#    #+#             */
/*   Updated: 2024/05/24 04:49:43 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	pars_unset(char *str, t_list **env, t_list **exp_var, t_code *code)
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
				ft_unset(env, exp_var, unset[i], code);
				i++;
			}
		}
	free_double_tabs(unset);
}

