/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 03:43:21 by almichel          #+#    #+#             */
/*   Updated: 2024/08/06 16:52:16 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		is_a_builtin(char *cmd)
{
	char **cmd_splitted;
	int	flag;

	flag = -1;
	cmd_splitted = ft_split(cmd, ' ');
	if (ft_strcmp(cmd_splitted[0], "echo") == 0)
		flag = 1;
	else if (ft_strcmp(cmd_splitted[0], "export") == 0)
		flag = 1;
	else if (ft_strcmp(cmd_splitted[0], "unset") == 0)
		flag = 1;
	else if (ft_strcmp(cmd_splitted[0], "exit") == 0)
		flag = 1;
	else if (ft_strcmp(cmd_splitted[0], "cd") == 0)
		flag = 1;
	else if (strcmp(cmd_splitted[0], "env") == 0)
		flag = 1;
	else if (strcmp(cmd_splitted[0], "pwd") == 0)
		flag = 1;
	free_double_tabs(cmd_splitted);
	return (flag);
}

void	exec_redirection(char *redir, int fd, int *flag)
{
	if (redir)
	{
		if (ft_strcmp(redir, ">") == 0 || ft_strcmp(redir, ">>") == 0)
			dup2(fd, STDOUT_FILENO);
		else if (ft_strcmp(redir, "<") == 0)
		{
			dup2(fd, STDIN_FILENO);
			*flag = 0;
		}
	}
}

int		exec_builtin(t_token *cur, t_list **env, t_list **exp_var, t_data *data, int fd)
{
	int len;
	char **cmd_splitted;

	fd = fd + 0;
	len = ft_strlen_double_tab(cur->redir);
	if (len != 0)
	{
		len--;
		if (ft_strcmp(cur->redir[len], ">") == 0 || ft_strcmp(cur->redir[len], ">>") == 0)
		{	
					dup2(fd, STDOUT_FILENO);
		}
		else if (ft_strcmp(cur->redir[len], "<") == 0)
		{
			if(dup2(fd, STDIN_FILENO) == -1)
				perror("dup2");
		}
		close(fd);
	}
	cmd_splitted = cur->cmd_pipex;
	if (ft_strcmp(get_cmd(cur), "echo") == 0)
		ft_echo(cur, &fd);
	if (ft_strcmp(get_cmd(cur), "export") == 0)
		pars_export(cur, env, exp_var, data);
	else if (ft_strcmp(get_cmd(cur), "unset") == 0)
		pars_unset(cur, env, exp_var, data);
	else if (ft_strcmp(get_cmd(cur), "pwd") == 0)
		print_pwd(get_cmd(cur), data);
	else if (ft_strlen_double_tab(cmd_splitted) > 1 && ft_strcmp(get_cmd(cur), "cd") == 0 && ft_strcmp(cur->next->content, "~") == 0)
		ft_cd_home(data, env);
	else if (ft_strcmp(get_cmd(cur), "cd") == 0)
		ft_cd(cur, env, data);
	else if (strcmp(get_cmd(cur), "env") == 0)
		print_env(env, exp_var, data);
	else if (ft_strcmp(get_cmd(cur), "exit") == 0)
	{
		ft_exit(cur, env, exp_var, data);
		return (-1);
	}
	return (0);
}
