/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 03:43:21 by almichel          #+#    #+#             */
/*   Updated: 2024/05/25 04:49:21 by almichel         ###   ########.fr       */
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

void	exec_builtin(char *cmd, t_list **env, t_list **exp_var, t_code *code)
{
	char **cmd_splitted;
	
	cmd_splitted = ft_split(cmd, ' ');
	//if (ft_strcmp(cmd_splitted[0], "echo") == 0)
	if (ft_strcmp(cmd_splitted[0], "export") == 0)
		pars_export(cmd, env, exp_var, code);
	else if (ft_strcmp(cmd_splitted[0], "unset") == 0)
		pars_unset(cmd, env, exp_var, code);
	else if (ft_strcmp(cmd_splitted[0], "pwd") == 0)
		print_pwd(cmd_splitted[0], code);
}
