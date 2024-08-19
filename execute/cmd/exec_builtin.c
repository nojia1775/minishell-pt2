/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 03:43:21 by almichel          #+#    #+#             */
/*   Updated: 2024/08/19 08:18:25 by codespace        ###   ########.fr       */
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

int	exec_builtin(t_token *cur, t_global *global, int fd)
{
	int len;
	char **cmd_splitted;
	int redir_flag;
	int sv;
	
	redir_flag = 0;
	fd = fd + 0;
	len = ft_strlen_double_tab(cur->redir);
	if (len != 0)
	{
		len--;
		while(ft_strcmp(cur->redir[len], "<<") == 0 && len > 0)
			len--;
		if (ft_strcmp(cur->redir[len], ">") == 0 || ft_strcmp(cur->redir[len], ">>") == 0)
			dup2(fd, STDOUT_FILENO);
		else if (ft_strcmp(cur->redir[len], "<") == 0)
		{
			redir_flag = 1;
			sv = dup(STDIN_FILENO);
			if(dup2(fd, STDIN_FILENO) == -1)
				perror("dup2");
		}
	}
	cmd_splitted = cur->cmd_pipex;
	if (ft_strcmp(get_cmd(cur), "echo") == 0)
		ft_echo(cur, &fd, global->data, redir_flag);
	if (ft_strcmp(get_cmd(cur), "export") == 0)
		pars_export(cur, global);
	else if (ft_strcmp(get_cmd(cur), "unset") == 0)
		pars_unset(cur, global);
	else if (ft_strcmp(get_cmd(cur), "pwd") == 0)
		print_pwd(get_cmd(cur), global->data);
	else if (ft_strlen_double_tab(cmd_splitted) > 1 && ft_strcmp(get_cmd(cur), "cd") == 0 && ft_strcmp(cur->next->content, "~") == 0)
		ft_cd_home(global);
	else if (ft_strcmp(get_cmd(cur), "cd") == 0)
		ft_cd(cur, global);
	else if (strcmp(get_cmd(cur), "env") == 0)
		print_env(&global->data->env, &global->data->exp_var, global->data);
	else if (ft_strcmp(get_cmd(cur), "exit") == 0)
	{
		if (cur->flag == 1)
			close(fd);
		exit(ft_exit(cur, global));
	}
	if (cur->flag == 1)
	{
		if (redir_flag)
			dup2(sv, STDIN_FILENO);
		close(fd);
	}
	return (0);
}
