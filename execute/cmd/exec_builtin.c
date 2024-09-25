/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 03:43:21 by almichel          #+#    #+#             */
/*   Updated: 2024/09/25 16:22:38 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_a_builtin(char *cmd)
{
	char	**cmd_splitted;
	int		flag;

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

static void	pars_builtin(t_token *cur, t_global *global, int redir_flag,
	int **fd)
{
	if (ft_strcmp(get_cmd(cur), "echo") == 0)
		ft_echo(cur, fd[0], global->data, redir_flag);
	else if (ft_strcmp(get_cmd(cur), "export") == 0)
		pars_export(cur, global);
	else if (ft_strcmp(get_cmd(cur), "unset") == 0)
		pars_unset(cur, global);
	else if (ft_strcmp(get_cmd(cur), "pwd") == 0)
		print_pwd(get_cmd(cur), global->data);
	else if (ft_strcmp(get_cmd(cur), "cd") == 0)
		ft_cd(cur, global);
	else if (ft_strcmp(get_cmd(cur), "env") == 0)
	{
		print_env(&global->data->env, &global->data->exp_var,
			global->data);
	}
	else if (ft_strcmp(get_cmd(cur), "exit") == 0 && many_arg(cur) == 0)
		ft_no_exit();
	else if (ft_strcmp(get_cmd(cur), "exit") == 0 && many_arg(cur) != 0)
	{
		if (cur->flag == 1)
			close(*fd[0]);
		close(*fd[1]);
		exit(ft_exit(cur, global));
	}
}

static void	len_not_null(t_vars_2 *vars, t_token *cur, int *fd)
{
	int	i;

	vars->len -= 1;
	i = 0;
	while (cur->redir[i])
	{
		if (ft_strcmp(cur->redir[i], "<") == 0)
			dup2(cur->fd_out, STDIN_FILENO);
		if (ft_strcmp(cur->redir[i], "<<") == 0)
			dup2(cur->fd, STDIN_FILENO);
		i++;
	}
	while (ft_strcmp(cur->redir[vars->len], "<<") == 0 && vars->len > 0)
	{
		dup2(cur->fd, STDIN_FILENO);
		vars->len -= 1;
	}
	if (ft_strcmp(cur->redir[vars->len], ">") == 0
		|| ft_strcmp(cur->redir[vars->len], ">>") == 0)
		dup2(*fd, STDOUT_FILENO);
}

int	exec_builtin(t_token *cur, t_global *global, int *fd, int sv)
{
	t_vars_2	vars;
	int			*fds[2];

	fds[0] = fd;
	fds[1] = &sv;
	vars.redir_flag = 0;
	vars.len = ft_strlen_double_tab(cur->redir);
	if (vars.len != 0)
		len_not_null(&vars, cur, fd);
	pars_builtin(cur, global, vars.redir_flag, fds);
	if (cur->flag == 1)
		close(*fd);
	dup2(sv, STDOUT_FILENO);
	close(sv);
	free_reset_global(global);
	return (0);
}
