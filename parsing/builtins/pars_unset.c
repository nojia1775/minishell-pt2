/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 02:08:02 by almichel          #+#    #+#             */
/*   Updated: 2024/09/14 13:08:00 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pars_unset(t_token *cur, t_global *global)
{
	char	**unset;
	int		i;

	i = 1;
	unset = cur->cmd_pipex;
	global->data->code = 0;
	g_sigint_received = 0;
	if (!unset[1])
	{
		free_double_tabs(unset);
		return ;
	}
	else
	{
		while (unset[i])
		{
			ft_unset(&global->data->env, &global->data->exp_var,
				cur->next->content, global->data);
			cur = cur->next;
			i++;
		}
	}
}
