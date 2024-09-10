/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:25:05 by nadjemia          #+#    #+#             */
/*   Updated: 2024/09/10 14:25:26 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	inredir_append(t_token *cur, int *fd, t_data *data, int i)
{
	if (ft_strcmp(cur->redir[i], ">>") == 0)
	{
		*fd = open(cur->files[i], O_WRONLY | O_APPEND, 0644);
		if (access(cur->files[i], W_OK) == -1
			&& access(cur->files[i], F_OK) == 0)
		{
			ft_putstr_msg(": Permission denied\n", 2, cur->files[i]);
			data->code = 1;
			return (-1);
		}
		else
		{
			*fd = open(cur->files[i], O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (access(cur->files[i], R_OK) != 0)
			{
				ft_putstr_msg(": Permission denied\n", 2, cur->files[i]);
				data->code = 1;
				return (-1);
			}
			cur->flag = 1;
			data->code = 0;
		}
	}
	return (1);
}

static int	inredir(t_token *cur, int *fd, t_data *data, int i)
{
	if (ft_strcmp(cur->redir[i], ">") == 0)
	{
		*fd = open(cur->files[i], O_WRONLY | O_TRUNC, 0644);
		if (access(cur->files[i], W_OK) == -1
			&& access(cur->files[i], F_OK) == 0)
		{
			ft_putstr_msg(": Permission denied\n", 2, cur->files[i]);
			data->code = 1;
			return (-1);
		}
		else
		{
			*fd = open(cur->files[i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (access(cur->files[i], R_OK) != 0)
			{
				data->code = 1;
				ft_putstr_msg(": Permission denied\n", 2, cur->files[i]);
				return (-1);
			}
			cur->flag = 1;
			data->code = 0;
		}
	}
	return (1);
}

static int	outredir(t_token *cur, int *fd, t_data *data, int i)
{
	if (ft_strcmp(cur->redir[i], "<") == 0)
	{
		if (access(cur->files[i], F_OK) != 0)
		{
			ft_putstr_msg(": No such file or directory\n", 2, cur->files[i]);
			data->code = 1;
			return (-1);
		}
		else
		{
			*fd = open(cur->files[i], O_RDONLY);
			if (access(cur->files[i], R_OK) != 0)
			{
				ft_putstr_msg(": Permission denied\n", 2, cur->files[i]);
				data->code = 1;
				return (-1);
			}
			cur->flag = 1;
			data->code = 0;
		}
	}
	return (1);
}

static int	heredoc(t_token *cur, int i, t_global *global)
{
	int	fd;

	if (ft_strcmp(cur->redir[i], "<<") == 0)
	{
		if (here_doc(cur->files[i], cur, global) == -1)
			return (-1);
		fd = open(cur->here_file, O_RDONLY);
		if (fd == -1)
			return (-1);
		if (ft_strcmp(get_cmd(cur), "<<") && !cur->redir[i + 1]
			&& ft_strcmp(get_cmd(cur), "<"))
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				perror("dup2");
		}
		close(fd);
		unlink(cur->here_file);
		free(cur->here_file);
	}
	return (1);
}

//Check la redirection et agit agit en consequences
int	check_redirection(t_token *cur, int *fd, t_data *data)
{
	int	i;

	i = 0;
	cur->flag = 0;
	if (cur->redir)
	{
		while (cur->redir[i])
		{
			if (inredir_append(cur, fd, data, i) == -1)
				return (-1);
			if (inredir(cur, fd, data, i) == -1)
				return (-1);
			if (outredir(cur, fd, data, i) == -1)
				return (-1);
			i++;
		}
	}
	return (0);
}

int  open_heredoc(t_token *cur, t_global *global, int sv, int j)
{
	int	i;

	i = 0;
	if (cur->redir)
	{
		while (cur->redir[i])
		{
			if (heredoc(cur, i, global) == -1)
				return (dup2(sv, STDIN_FILENO), -1);
			if (global->tokens[j + 1] == NULL && !cur->redir[i + 1])
				break ;
			dup2(sv, STDIN_FILENO);
			i++;
		}
	}
	return (0);
}