/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:27:40 by almichel          #+#    #+#             */
/*   Updated: 2024/08/09 13:22:50 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pars_export(t_token *cur, t_global *global)
{
	char **export;
	int		i;

	i = 1;
	export = cur->cmd_pipex;
	if (export[1] == NULL)
	{
		ft_export(&global->env, &global->exp_var);
		return;
	}
	else 
	{
		while (export[i])
		{
			if (pars_exp_var(export[i]) != -1)
			{
				export_variable(&global->env, &global->exp_var, cur->next->content, global->data);
				cur = cur->next;
				global->data->code = 0;
			}
			else 
				global->data->code = 1;
			i++;
		}
	}
}

int 	pars_exp_var(char *str)
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
