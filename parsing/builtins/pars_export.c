/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:27:40 by almichel          #+#    #+#             */
/*   Updated: 2024/09/05 12:16:38 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pars_export(t_token *cur, t_global *global)
{
	int		i;

	if (cur->cmd_pipex[1] == NULL)
	{
		ft_export(&global->data->env, &global->data->exp_var);
		return ;
	}
	else
	{
		i = 1;
		while (global->cur->cmd_pipex[i])
		{
			if (pars_exp_var(cur->cmd_pipex[i]) != -1)
			{
				export_variable(&global->data->env, &global->data->exp_var,
					cur->next->content, global->data);
				cur = cur->next;
				global->data->code = 0;
			}
			else
				global->data->code = 1;
			i++;
		}
	}
}

int	pars_exp_var(char *str)
{
	if (checking_if_alpha(str) == -1)
	{
		ft_simple_err("export: ", 2);
		ft_putstr_msg(": not a valid identifier\n", 2, str);
		return (-1);
	}
	if (str[0] == '=')
	{
		ft_simple_err("export: ", 2);
		ft_putstr_msg(": not a valid identifier\n", 2, str);
		return (-1);
	}
	return (0);
}
