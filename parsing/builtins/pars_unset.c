/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 02:08:02 by almichel          #+#    #+#             */
/*   Updated: 2024/07/28 02:45:02 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	pars_unset(t_token *cur, t_list **env, t_list **exp_var, t_data *data)
{
	char **unset;
	int		i;

	i = 1;
	unset = cur->cmd_pipex;
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
				ft_unset(env, exp_var, cur->next->content, data);
				cur = cur->next;
				i++;
			}
		}
}

