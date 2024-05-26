/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 03:43:21 by almichel          #+#    #+#             */
/*   Updated: 2024/05/26 04:04:53 by almichel         ###   ########.fr       */
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

int		exec_builtin(t_data *data, t_list **env, t_list **exp_var)
{
	char **cmd_splitted;
	
	cmd_splitted = ft_split(data->str, ' ');
	//if (ft_strcmp(cmd_splitted[0], "echo") == 0)
	if (ft_strcmp(cmd_splitted[0], "export") == 0)
		pars_export(data, env, exp_var);
	else if (ft_strcmp(cmd_splitted[0], "unset") == 0)
		pars_unset(data, env, exp_var);
	else if (ft_strcmp(cmd_splitted[0], "pwd") == 0)
		print_pwd(cmd_splitted[0], data);
	else if (cmd_splitted[1])
	{
		if (ft_strcmp(cmd_splitted[0], "cd") == 0 && ft_strcmp(cmd_splitted[1], "~") == 0)
			ft_cd_home(data, env);
	}
	else if (ft_strcmp(cmd_splitted[0], "cd") == 0)
		ft_cd(data, env, exp_var);
	else if (ft_strcmp(cmd_splitted[0], "exit") == 0)
	{
		ft_exit(data, env, exp_var);
		return (-1);
	}
	return (0);
}
