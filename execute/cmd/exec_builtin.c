/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 03:43:21 by almichel          #+#    #+#             */
/*   Updated: 2024/09/14 13:37:23 by noah             ###   ########.fr       */
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
	int *fd)
{
	if (ft_strcmp(get_cmd(cur), "echo") == 0)
		ft_echo(cur, fd, global->data, redir_flag);
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
	else if (ft_strcmp(get_cmd(cur), "exit") == 0)
	{
		if (cur->flag == 1)
			close(*fd);
		exit(ft_exit(cur, global));
	}
}

typedef struct s_vars
{
	int	len;
	int	redir_flag;
	int	sv;
}	t_vars;

static void	len_not_null(t_vars *vars, t_token *cur, int *fd)
{
	vars->len -= 1;
	while (ft_strcmp(cur->redir[vars->len], "<<") == 0 && vars->len > 0)
		vars->len -= 1;
	if (ft_strcmp(cur->redir[vars->len], ">") == 0
		|| ft_strcmp(cur->redir[vars->len], ">>") == 0)
		dup2(*fd, STDOUT_FILENO);
	else if (ft_strcmp(cur->redir[vars->len], "<") == 0)
	{
		vars->redir_flag = 1;
		vars->sv = dup(STDOUT_FILENO);
		if (dup2(*fd, STDIN_FILENO) == -1)
			perror("dup2");
	}
}

int	exec_builtin(t_token *cur, t_global *global, int fd, int sv)
{
	t_vars	vars;

	vars.redir_flag = 0;
	vars.len = ft_strlen_double_tab(cur->redir);
	if (vars.len != 0)
		len_not_null(&vars, cur, &fd);
	pars_builtin(cur, global, vars.redir_flag, &fd);
	if (cur->flag == 1)
	{
		if (vars.redir_flag)
			dup2(vars.sv, STDIN_FILENO);
		close(fd);
	}
	dup2(sv, STDIN_FILENO);
	free_reset_global(global);
	return (0);
}
