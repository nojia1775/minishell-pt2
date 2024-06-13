/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:27:40 by almichel          #+#    #+#             */
/*   Updated: 2024/06/13 18:47:31 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pars_export(char *str, t_list **env, t_list **exp_var, t_data *data)
{
	char **export;
	int		i;

	i = 1;
	export = ft_split(str, ' ');
	if (export[1] == NULL)
	{
		ft_export(data, env, exp_var);
		free_double_tabs(export);
		return;
	}
	else 
		{
			while (export[i])
			{
				export[i] = pars_exp_var(export[i]);
				i++;
			}
		}
	free_double_tabs(export);
}

char	*pars_exp_var(char *str)
{
	/*if (checking_nbr_quotes(str) == -1)
	{
		ft_putstr_msg(": not a valid identifier\n", 2, str);
			return (str);
	}*/
	if (checking_order_quotes(str) == -1)
	{
		str = del_outside_quotes(str);
		ft_putstr_msg(": not a valid identifier\n", 2, str);
		return (str);
	}
	else if (checking_order_quotes(str) == 1)
	{
		str = del_all_quotes(str);
	}
	if (checking_if_alpha(str) == -1)
	{
		ft_putstr_msg(": not a valid identifier\n", 2, str);
		return (str);
	}
	if (str[0] == '=')
	{
		ft_putstr_msg(": not a valid identifier\n", 2, str);
		return (str);
	}
	return (str);
}

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
}




