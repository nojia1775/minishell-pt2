/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:08:30 by almichel          #+#    #+#             */
/*   Updated: 2024/08/06 16:23:30 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// Fonction echo, c'est juste un printf et je check si y'a l'option -n
void	ft_echo(t_token *cur, int n_option, int *fd, int flag_redir, t_data *data)
{
	int i;
	int len;
	int flag;

	flag = -1;
	len = ft_strlen(cur->cmd_pipex[1]);
	//cur->cmd_pipex = find_echo_var(cur->cmd_pipex, env, exp_var, &flag);
	if (ft_strcmp("$?", cur->cmd_pipex[1]) == 0)
	{
		ft_printf("%d", data->code);
	}
	else
	{
		if (flag == 1)
			i = len + 1;
		else
			i = 0;
		while (data->str[i])
		{
			if (*fd != -1 && flag_redir != 0)
				write((*fd), &cur->cmd_pipex[i], 1);
			else
				write(1, &cur->cmd_pipex[i], 1);
			i++;
		}
	}
	if (n_option != -1)
		write(1, "\n", 1);
	if (flag == 1)
		free(cur->cmd_pipex);
}