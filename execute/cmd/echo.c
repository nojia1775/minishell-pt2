/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:08:30 by almichel          #+#    #+#             */
/*   Updated: 2024/05/08 15:09:49 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Fonction qui cherche si ya un $NomDeVariable pour la print avec echo
char	*find_echo_var(char *str, t_list **env, t_list **exp_var, int *flag)
{
	char	**total_env;
	int		i;

	i = 0;
	total_env = stock_total_env(env, exp_var);
	while (total_env[i])
	{
		if (ft_strncmp(str + 1, total_env[i], ft_strlen(str) - 1) == 0)
		{
			*flag = 1;
			str = ft_strdup(total_env[i]);
		}
		i++;
	}
	i = 0;
	while (total_env[i])
	{
		free(total_env[i]);
		i++;
	}
	free(total_env);
	return (str);
}

// Fonction echo, c'est juste un printf et je check si y'a l'option -n
void	ft_echo(char *str, int n_option, t_list **env, t_list **exp_var,
			int *fd, t_code *code, int flag_redir)
{
	int i;
	int len;
	int flag;

	flag = -1;
	len = ft_strlen(str);
	str = find_echo_var(str, env, exp_var, &flag);
	if (ft_strcmp("$?", str) == 0)
	{
		ft_printf("%d", code->code);
	}
	else
	{
		if (flag == 1)
			i = len + 1;
		else
			i = 0;
		while (str[i])
		{
			if (*fd != -1 && flag_redir != 0)
				write((*fd), &str[i], 1);
			else
				write(1, &str[i], 1);
			i++;
		}
	}
	if (n_option != -1)
		write(1, "\n", 1);
	if (flag == 1)
		free(str);
}