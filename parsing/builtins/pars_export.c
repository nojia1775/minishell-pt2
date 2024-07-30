/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:27:40 by almichel          #+#    #+#             */
/*   Updated: 2024/07/29 17:40:35 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pars_export(t_token *cur, t_list **env, t_list **exp_var, t_data *data)
{
	char **export;
	int		i;

	i = 1;
	export = cur->cmd_pipex;
	if (export[1] == NULL)
	{
		ft_export(env, exp_var);
		return;
	}
	else 
	{
		while (export[i])
		{
			if (pars_exp_var(export[i]) != -1)
			{
				export_variable(env, exp_var, cur->next->content, data);
				cur = cur->next;
				data->code = 0;
			}
			else 
				data->code = 1;
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
