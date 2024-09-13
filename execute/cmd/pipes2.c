/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:18:52 by almichel          #+#    #+#             */
/*   Updated: 2024/09/13 16:00:18 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_pipes_process1(t_token *cur, t_pipes *pipes, char *envp[], int fd)
{
	int	len;

	len = 0;
	len = ft_strlen_double_tab(cur->redir);
	if (len != 0)
	{
		len--;
		while (ft_strcmp(cur->redir[len], "<<") == 0 && len > 0)
		{
			dup2(cur->fd, STDOUT_FILENO);
			len--;
		}
		if (ft_strcmp(cur->redir[len], ">") == 0
			|| ft_strcmp(cur->redir[len], ">>") == 0)
			dup2(fd, STDOUT_FILENO);
		else if (ft_strcmp(cur->redir[len], "<") == 0)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				perror("dup2");
		}
		if (cur->flag == 1)
			close(fd);
	}
	execve(get_cmd(cur), get_cmd_pipex(cur), envp);
	ft_relative_path1(get_cmd_pipex(cur), envp, get_cmd(cur), pipes);
}

void	child_pipes_process2(t_token *cur, t_global *global, int sv, int fd)
{
	int	len;

	len = 0;
	len = ft_strlen_double_tab(cur->redir);
	dup2(cur->fd, STDIN_FILENO);
	if (len != 0)
	{
		len--;
		while (ft_strcmp(cur->redir[len], "<<") == 0 && len > 0)
		{
			dup2(cur->fd, STDIN_FILENO);
			close(cur->fd);
			len--;
		}
		if (ft_strcmp(cur->redir[len], ">") == 0
			|| ft_strcmp(cur->redir[len], ">>") == 0)
			dup2(fd, STDOUT_FILENO);
		else if (ft_strcmp(cur->redir[len], "<") == 0)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				perror("dup2");
		}
		if (cur->flag == 1)
			close(fd);
	}
	else
		dup2(sv, STDOUT_FILENO);
	execve(get_cmd(cur), get_cmd_pipex(cur), global->data->envv);
	ft_relative_path2(get_cmd_pipex(cur),
		global->data->envv, get_cmd(cur), global->pipes);
}

void	ft_relative_path1(char **cmd_pipex, char **envp, char *cmd,
	t_pipes *pipes)
{
	int	i;

	i = -1;
	if (envp[0] != NULL)
	{
		while (envp[++i])
		{
			if (ft_strncmp("PATH", envp[i], 4) == 0)
				pipes->good_line_envp = envp[i];
		}
		if (pipes->good_line_envp != NULL)
		{
			pipes->good_path = ft_split(pipes->good_line_envp, ':');
			i = -1;
			while (pipes->good_path[++i])
			{
				pipes->good_cmd = ft_strjoin_cmd(pipes->good_path[i], cmd);
				execve(pipes->good_cmd, cmd_pipex, envp);
				free(pipes->good_cmd);
			}
		}
	}
	if (pipes->good_line_envp != NULL)
		free_double_tabs(pipes->good_path);
	ft_putstr_fd_pipes(":  command not found\n", 2, cmd);
}

void	ft_relative_path2(char **cmd_pipex, char **envp, char *cmd,
	t_pipes *pipes)
{
	int	i;

	i = -1;
	if (envp[0] != NULL)
	{
		while (envp[++i])
		{
			if (ft_strncmp("PATH", envp[i], 4) == 0)
				pipes->good_line_envp = envp[i];
		}
		if (pipes->good_line_envp != NULL)
		{
			pipes->good_path = ft_split(pipes->good_line_envp, ':');
			i = -1;
			while (pipes->good_path[++i])
			{
				pipes->good_cmd = ft_strjoin_cmd(pipes->good_path[i], cmd);
				execve(pipes->good_cmd, cmd_pipex, envp);
				free(pipes->good_cmd);
			}
		}
	}
	if (pipes->good_line_envp != NULL)
		free_double_tabs(pipes->good_path);
	ft_putstr_fd_pipes(": command not found \n", 2, cmd);
}
