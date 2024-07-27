/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 02:08:02 by almichel          #+#    #+#             */
/*   Updated: 2024/07/25 19:16:21 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	pars_unset(t_token *cur, t_list **env, t_list **exp_var, t_data *data)
{
	char **unset;
	int		i;

	i = 1;
	unset = ft_split(cur->cmd_pipex, ' ');
	data->code =  0;
	if (!unset[1])
	{
		free_double_tabs(unset);
		return;
	}
	else 
		{
			while (unset[i])
			{
				ft_unset(env, exp_var, unset[i], data);
				i++;
			}
		}
	free_double_tabs(unset);
}

