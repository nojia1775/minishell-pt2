/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:08:30 by almichel          #+#    #+#             */
/*   Updated: 2024/08/09 15:44:12 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	write_fd(char *str, int fd, char *next)
{
	ft_putstr_fd(str, fd);
	if (next)
		ft_putstr_fd(" ", fd);
}

static int	is_n_option(char *str)
{
	int	i;
	
	if (str[0] != '-')
		return (0);
	if (str[1] != 'n')
		return (0);
	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

void	ft_echo(t_token *cur, int *fd, t_data *data)
{
	int	option;
	int	flag;
	int	i;
	
	i = 0;
	option = 1;
	flag = 1;
	if (!cur->next)
		ft_putstr_fd("\n", *fd);
	if (cur->next && !is_n_option(cur->cmd_pipex[1]))
	{
		option = 0;
		flag = 0;
	}
	while (cur->cmd_pipex[++i])
	{
		if (flag)
		{
			if (!is_n_option(cur->cmd_pipex[i]))
			{
				write_fd(cur->cmd_pipex[i], *fd, cur->cmd_pipex[i + 1]);
				flag = 0;
			}
		}
		else
			write_fd(cur->cmd_pipex[i], *fd, cur->cmd_pipex[i + 1]);
	}
	if (!option)
		ft_putstr_fd("\n", *fd);
	data->code = 0;
}