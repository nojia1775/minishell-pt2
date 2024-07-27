/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:18:52 by almichel          #+#    #+#             */
/*   Updated: 2024/07/27 04:48:24 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_pipes_process1(t_token *cur, t_pipes *pipes, char *envp[], int fd)
{
	int		i;
	char	**absolut_path;
	char	**cmd1;
	int 	len;

	len = 0;
	len = ft_strlen_double_tab(cur->redir);
	if (len != 0)
	{
		len--;
		if (ft_strcmp(cur->redir[len], ">") == 0 || ft_strcmp(cur->redir[len], ">>") == 0)
			dup2(fd, STDOUT_FILENO);
		else if (ft_strcmp(cur->redir[len], "<") == 0)
		{
			if(dup2(fd, STDIN_FILENO) == -1)
				perror("dup2");
		}
		close(fd);
	}
	cmd1 = ft_split(cur->cmd_pipex, ' ');
	i = 0;
	
	absolut_path = ft_split(cur->cmd_pipex, ' ');
	execve(absolut_path[0], cmd1, envp);
	while (absolut_path[i])
		i++;
	free_double_tabs(absolut_path);
	i = 0;
	ft_relative_path1(pipes, envp, i, cur);
	i = -1;
	while (cmd1[++i] != NULL)
		free(cmd1[i]);
	free(cmd1);
}

void	child_pipes_process2(t_token *cur, t_pipes *pipes, char *envp[], int sv, int fd)
{
	int		i;
	char	**absolut_path;
	char	**cmd2;
	int 	len;

	len = 0;
	len = ft_strlen_double_tab(cur->redir);
	if (len != 0)
	{
		len--;
		if (ft_strcmp(cur->redir[len], ">") == 0 || ft_strcmp(cur->redir[len], ">>") == 0)
			dup2(fd, STDOUT_FILENO);
		else if (ft_strcmp(cur->redir[len], "<") == 0)
		{
			if(dup2(fd, STDIN_FILENO) == -1)
				perror("dup2");
		}
		close(fd);
	}
	else
		dup2(sv, STDOUT_FILENO);
	cmd2 = ft_split(cur->cmd_pipex, ' ');
	i = 0;
	absolut_path = ft_split(cur->cmd_pipex, ' ');
	execve(absolut_path[0], cmd2, envp);
	while (absolut_path[i])
		i++;
	free_double_tabs(absolut_path);
	i = 0;
	ft_relative_path2(pipes, envp, i, cur);
	while (cmd2[i] != NULL)
	{
		free(cmd2[i]);
		i++;
	}
	free(cmd2);
}

void	ft_relative_path1(t_pipes *pipes, char **envp, int i, t_token *cur)
{
	pipes->splited_cmd1 = ft_split(cur->cmd_pipex, ' ');
	if (envp[0] != NULL)
	{
		while (envp[i])
		{
			if (ft_strncmp("PATH", envp[i], 4) == 0)
				pipes->good_line_envp = envp[i];
			i++;
		}
		if (pipes->good_line_envp != NULL)
		{
			pipes->good_path = ft_split(pipes->good_line_envp, ':');
			i = -1;
			while (pipes->good_path[++i])
			{
				pipes->good_cmd = ft_strjoin_cmd(pipes->good_path[i], cur->cmd_pipex);
				execve(pipes->good_cmd, pipes->splited_cmd1, envp);
				free(pipes->good_cmd);
			}
		}
	}
	if (pipes->good_line_envp != NULL)
		free_double_tabs(pipes->good_path);
	ft_putstr_fd_pipes(":  command not found\n", 2, cur->cmd_pipex);
	free_double_tabs(pipes->splited_cmd1);
}

void	ft_relative_path2(t_pipes *pipes, char **envp, int i, t_token *cur)
{
	pipes->splited_cmd2 = ft_split(cur->cmd_pipex, ' ');
	if (envp[0] != NULL)
	{
		while (envp[i])
		{
			if (ft_strncmp("PATH", envp[i], 4) == 0)
				pipes->good_line_envp = envp[i];
			i++;
		}
		if (pipes->good_line_envp != NULL)
		{
			pipes->good_path = ft_split(pipes->good_line_envp, ':');
			i = -1;
			while (pipes->good_path[++i])
			{
				pipes->good_cmd = ft_strjoin_cmd(pipes->good_path[i], cur->cmd_pipex);
				execve(pipes->good_cmd, pipes->splited_cmd2, envp);
				free(pipes->good_cmd);
			}
		}
	}
	if (pipes->good_line_envp != NULL)
		free_double_tabs(pipes->good_path);
	ft_putstr_fd_pipes(": command not found \n", 2, cur->cmd_pipex);
	free_double_tabs(pipes->splited_cmd2);
}
