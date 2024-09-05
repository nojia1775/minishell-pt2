/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:17:07 by almichel          #+#    #+#             */
/*   Updated: 2024/09/05 12:12:46 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	setup_exe_fork(t_global *global, int *fd, int *status, t_token *cur)
{
	pid_t	pid;

	pid = fork();
	if (set_exec_signals(data) == -1)
		return(0);
	if (pid == 0)
	{
		global->data->code = 0;
		if (check_redirection(cur, fd, global->data, global) == 0)
			check_and_exe_cmd(cur, global, *fd);
		exit(127);
	}
	else if (pid > 0)
	{
		//printf("***** ICI\n");
		waitpid(pid, status, 0);
		free_reset_global(global);
		if (WIFEXITED(*status))
			global->data->code = WEXITSTATUS(*status);
	}
	else
		perror("fork");
	return (0);
}

// Fonction principale executent une commande simple du genre ls -l par exemple
int	setup_exe_simple_cmd(t_token *cur, t_global *global)
{
	int		status;
	int		fd;

	status = 0;
	fd = STDOUT_FILENO;
	if (set_exec_signals(global->data) == -1)
		return (0);
	if (is_a_builtin(get_cmd(cur)) == 1)
	{
		if (check_redirection(cur, &fd, global->data, global) == 0)
			return (exec_builtin(cur, global, fd));
		else
		{
			global->data->code = 1;
			return (1);
		}
	}
	setup_exe_fork(global, &fd, &status, cur);
	return (0);
}

// fonction qui tente l'absolut path et s' il ne s'execute pas il
// test le relative path(fonction en dessous)
void	check_and_exe_cmd(t_token *cur, t_global *global, int fd)
{
	char	**total_env;
	int		len;

	len = 0;
	len = ft_strlen_double_tab(cur->redir);
	if (len != 0)
	{
		len--;
		while (ft_strcmp(cur->redir[len], "<<") == 0 && len > 0)
			len--;
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
	total_env = stock_total_env(&global->data->env, &global->data->exp_var);
	execve(get_cmd(cur), get_cmd_pipex(cur), total_env);
	ft_relative_path(get_cmd_pipex(cur), total_env, get_cmd(cur), global);
}

typedef struct s_vars
{
	char	*good_line_envp;
	char	**good_path;
	char	*good_cmd;
}	t_vars;

static void	if_envp(t_vars *vars, char **envp, char **cmd_pipex, char *cmd)
{
	int	i;

	i = 0;
	if (envp != NULL)
	{
		while (envp[i])
		{
			if (!ft_strncmp("PATH=", envp[i], 5))
				vars->good_line_envp = envp[i];
			i++;
		}
		if (vars->good_line_envp)
		{
			vars->good_path = ft_split(vars->good_line_envp, ':');
			i = -1;
			while (vars->good_path[++i])
			{
				vars->good_cmd = ft_strjoin_cmd(
						vars->good_path[i], cmd);
				execve(vars->good_cmd, cmd_pipex, envp);
				free(vars->good_cmd);
			}
		}
	}
}

// Fonction qui execute le relative path en testant tous les binaires de l'env
void	ft_relative_path(char **cmd_pipex, char **envp, char *cmd,
t_global *global)
{
	t_vars	vars;

	(void)global;
	vars.good_path = NULL;
	vars.good_line_envp = NULL;
	vars.good_cmd = NULL;
	if_envp(&vars, envp, cmd_pipex, cmd);
	if (vars.good_line_envp != NULL)
		free_double_tabs(vars.good_path);
	if (envp)
		free_double_tabs(envp);
	if (ft_strcmp(cmd, ">") && ft_strcmp(cmd, ">>")
		&& ft_strcmp(cmd, "<") && ft_strcmp(cmd, "<<"))
		ft_putstr_msg(": command not found\n", 2, cmd);
	//free_reset_global(global);
}
