/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:52:04 by nadjemia          #+#    #+#             */
/*   Updated: 2024/07/16 12:35:28 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_var(char *str, t_list **env, t_list **exp_var)
{
	char	**total_env;
	int		i;
	char	*value;
	char	*tmp;
	
	tmp = NULL;
	i = 0;
	total_env = stock_total_env(env, exp_var);
	while (total_env[i])
	{
		if (ft_strncmp(str, total_env[i], ft_strlen(str)) == 0)
			tmp = ft_strdup(total_env[i]);
		i++;
	}
	i = 0;
	while (total_env[i])
		free(total_env[i++]);
	free(total_env);
	if (!tmp)
		return (NULL);
	value = ft_strdup(tmp + ft_strlen_egal(str) + 1);
	free(tmp);
	return (value);
}
