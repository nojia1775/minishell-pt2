/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:52:04 by nadjemia          #+#    #+#             */
/*   Updated: 2024/05/24 02:40:38 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_var(char *str, t_list **env, t_list **exp_var)
{
	char	**total_env;
	int		i;
	
	
	i = 0;
	total_env = stock_total_env(env, exp_var);
	while (total_env[i])
	{
		if (ft_strncmp(str, total_env[i], ft_strlen(str)) == 0)
			str = ft_strdup(total_env[i]);
		i++;
	}
	i = 0;
	while (total_env[i])
	{
		free(total_env[i]);
		i++;
	}
	free(total_env);
	return (str + ft_strlen_egal(str) + 1);
}

int	parsing(char **input, t_list **env, t_list **exp_var)
{
	char	*result;

	result = quotes(*input, env, exp_var);
	if (!result)
		return (printf("minishell : Syntax error\n"), 0);
	*input = result;
//	printf("%s\n", result);
	return (1);
}
