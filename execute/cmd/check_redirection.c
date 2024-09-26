/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:25:05 by nadjemia          #+#    #+#             */
/*   Updated: 2024/09/26 14:42:43 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	close_norm(int fd)
{
	if (fd != -1)
		close(fd);
}

static int	inredir_append(t_token *cur, int *fd, int i)
{
	if (ft_strcmp(cur->redir[i], ">>") == 0)
	{
		*fd = open(cur->files[i], O_WRONLY | O_APPEND, 0644);
		if (access(cur->files[i], W_OK) == -1
			&& access(cur->files[i], F_OK) == 0)
		{
			ft_putstr_msg(": Permission denied\n", 2, cur->files[i]);
			g_sigint_received = 1;
			return (-1);
		}
		else
		{
			close_norm(*fd);
			*fd = open(cur->files[i], O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (access(cur->files[i], R_OK) != 0)
			{
				ft_putstr_msg(": Permission denied\n", 2, cur->files[i]);
				g_sigint_received = 1;
				return (-1);
			}
			cur->flag = 1;
			g_sigint_received = 0;
		}
	}
	return (1);
}

static int	inredir(t_token *cur, int *fd, int i)
{
	if (ft_strcmp(cur->redir[i], ">") == 0)
	{
		*fd = open(cur->files[i], O_WRONLY | O_TRUNC, 0644);
		if (access(cur->files[i], W_OK) == -1
			&& access(cur->files[i], F_OK) == 0)
		{
			ft_putstr_msg(": Permission denied\n", 2, cur->files[i]);
			g_sigint_received = 1;
			return (-1);
		}
		else
		{
			close_norm(*fd);
			*fd = open(cur->files[i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (access(cur->files[i], R_OK) != 0)
			{
				g_sigint_received = 1;
				ft_putstr_msg(": Permission denied\n", 2, cur->files[i]);
				return (-1);
			}
			cur->flag = 1;
			g_sigint_received = 0;
		}
	}
	return (1);
}

static int	outredir(t_token *cur, int i)
{
	if (ft_strcmp(cur->redir[i], "<") == 0)
	{
		if (access(cur->files[i], F_OK) != 0)
		{
			ft_putstr_msg(": No such file or directory\n", 2, cur->files[i]);
			g_sigint_received = 1;
			return (-1);
		}
		else
		{
			cur->fd_out = open(cur->files[i], O_RDONLY);
			if (access(cur->files[i], R_OK) != 0)
			{
				ft_putstr_msg(": Permission denied\n", 2, cur->files[i]);
				g_sigint_received = 1;
				return (-1);
			}
			g_sigint_received = 0;
		}
	}
	return (1);
}

//Check la redirection et agit agit en consequences
int	check_redirection(t_token *cur, int *fd, t_data *data)
{
	int	i;

	(void)data;
	i = 0;
	cur->flag = 0;
	if (cur->redir)
	{
		while (cur->redir[i])
		{
			if (inredir_append(cur, fd, i) == -1)
				return (-1);
			if (inredir(cur, fd, i) == -1)
				return (-1);
			if (outredir(cur, i) == -1)
				return (-1);
			i++;
		}
	}
	return (0);
}
