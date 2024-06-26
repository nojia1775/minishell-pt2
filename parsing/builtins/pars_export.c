/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:27:40 by almichel          #+#    #+#             */
/*   Updated: 2024/05/26 03:37:52 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pars_export(t_data *data, t_list **env, t_list **exp_var)
{
	char **export;
	int		i;

	i = 1;
	export = ft_split(data->str, ' ');
	if (export[1] == NULL)
	{
		ft_export(env, exp_var);
		free_double_tabs(export);
		return;
	}
	else 
		{
			while (export[i])
			{
				if (pars_exp_var(export[i]) != -1)
				{
					export_variable(env, exp_var, export[i], data);
					data->code = 0;
				}
				else 
					data->code = 1;
				i++;
			}
		}
	free_double_tabs(export);
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
/*
int	checking_order_quotes(char *str)
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
	if (count == 0 && count2 == 0)
		return (1);
	else if (count == 0 && count2 % 2 == 0)
		return (1);
	else if (count2 == 0 && count % 2 == 0)
		return (1);
	else
		return (-1);
}

char	*del_outside_quotes(char *str)
{
	char *temp;

	temp = malloc((ft_strlen(str) + 1)* sizeof(char));
	if (!temp)
		return (NULL);
	ft_strcpy_(temp, str);
	free(str);
	str = NULL;
	str = ft_strdup_outside_quotes(temp);
	free(temp);
	return (str);
	
}

char	*del_all_quotes(char *str)
{
	char	*temp;

	temp = malloc((ft_strlen(str) + 1)* sizeof(char));
	if (!temp)
		return (NULL);
	ft_strcpy_(temp, str);
	free(str);
	str = ft_strdup_quotes(temp);
	free(temp);
	return (str);
}*/



