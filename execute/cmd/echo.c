/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:08:30 by almichel          #+#    #+#             */
/*   Updated: 2024/09/18 10:58:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	write_fd(char *str, int fd, char *next, int redir_flag)
{
	if (redir_flag == 1)
	{
		printf("%s", str);
		if (next)
			printf(" ");
		return ;
	}
	ft_putstr_fd(str, fd);
	if (next)
		ft_putstr_fd(" ", fd);
}

static int	is_n_option(char *str)
{
	int	i;

	if (!str)
		return (0);
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

static void	loop(t_token *cur, int flag, int redir_flag, int fd)
{
	int	i;

	i = 0;
	while (cur->cmd_pipex[++i])
	{
		if (flag)
		{
			if (!is_n_option(cur->cmd_pipex[i]))
			{
				write_fd(cur->cmd_pipex[i], fd,
					cur->cmd_pipex[i + 1], redir_flag);
				flag = 0;
			}
		}
		else
		{
			write_fd(cur->cmd_pipex[i], fd,
				cur->cmd_pipex[i + 1], redir_flag);
		}
	}
}

void	ft_echo(t_token *cur, int *fd, t_data *data, int redir_flag)
{
	int	option;
	int	flag;

	(void)data;
	option = 1;
	flag = 1;
	if (!cur->next)
		ft_putstr_fd("\n", *fd);
	if (cur->next && !is_n_option(cur->cmd_pipex[1]))
	{
		option = 0;
		flag = 0;
	}
	loop(cur, flag, redir_flag, *fd);
	if (!option)
	{
		if (redir_flag == 1)
			printf("\n");
		else
			ft_putstr_fd("\n", *fd);
	}
	g_sigint_received = 0;
}
