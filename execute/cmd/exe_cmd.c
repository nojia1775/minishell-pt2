/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:17:07 by almichel          #+#    #+#             */
/*   Updated: 2024/09/26 14:56:35 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	setup_exe_fork(t_global *global, int *fd, int *status, t_token *cur)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		g_sigint_received = 0;
		if (check_redirection(cur, fd, global->data) == 0)
			check_and_exe_cmd(cur, global, *fd);
		exit(g_sigint_received);
	}
	else if (pid > 0)
	{
		if (cur->fd != -1)
			close(cur->fd);
		waitpid(pid, status, 0);
		free_reset_global(global);
		if (WIFEXITED(*status))
			g_sigint_received = WEXITSTATUS(*status);
	}
	else
		perror("fork");
}

// Fonction principale executent une commande simple du genre ls -l par exemple
int	setup_exe_simple_cmd(t_token *cur, t_global *global)
{
	int		status;
	int		fd;
	int		sv;

	status = 0;
	sv = dup(STDIN_FILENO);
	fd = 1;
	if (set_exec_signals(global->data) == -1)
		return (close(sv), 0);
	if (open_heredoc(cur, global, sv, 0) == -1)
		return (close(sv), 1);
	if (is_a_builtin(get_cmd(cur)) == 1)
	{
		if (check_redirection(cur, &fd, global->data) == 0)
			return (exec_builtin(cur, global, &fd, sv));
		else
		{
			g_sigint_received = 1;
			return (close(sv), 1);
		}
	}
	setup_exe_fork(global, &fd, &status, cur);
	dup2(sv, STDIN_FILENO);
	close(sv);
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
	dup_infile(cur, len, 1);
	if (len != 0)
	{
		len--;
		while (ft_strcmp(cur->redir[len], "<<") == 0 && len > 0)
			len--;
		if (ft_strcmp(cur->redir[len], ">") == 0
			|| ft_strcmp(cur->redir[len], ">>") == 0)
			dup2(fd, STDOUT_FILENO);
		if (cur->flag == 1)
			close(fd);
	}
	total_env = stock_total_env(&global->data->env, &global->data->exp_var);
	execve(get_cmd(cur), get_cmd_pipex(cur), total_env);
	ft_relative_path(get_cmd_pipex(cur), total_env, get_cmd(cur), global);
}

static void	if_envp(t_vars_1 *vars, char **envp, char **cmd_pipex, char *cmd)
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
	t_vars_1	vars;

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
	{
		ft_putstr_msg(": command not found\n", 2, cmd);
		g_sigint_received = 127;
	}
}
