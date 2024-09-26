/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:04:29 by almichel          #+#    #+#             */
/*   Updated: 2024/09/26 14:49:04 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_process_pipex(int *end, int *fd, t_global *global,
t_token *cur)
{
	if (dup2(end[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 (child - stdout)");
		close(end[0]);
		close(end[1]);
		exit(EXIT_FAILURE);
	}
	close(end[0]);
	close(end[1]);
	if (is_a_builtin(get_cmd(cur)) == 1)
	{
		if (check_redirection(cur, fd, global->data) == 0)
			exec_builtin(cur, global, fd, 1);
		exit(127);
	}
	if (check_redirection(cur, fd, global->data) == 0)
		child_pipes_process1(cur, global->pipes, global->data->envv, *fd);
	exit(127);
}

static void	child_process_main(t_vars_4 *vars, t_token *cur,
t_global *global, int sv)
{
	if (is_a_builtin(get_cmd(cur)) == 1)
	{
		if (check_redirection(cur, &vars->fd, global->data) == 0)
			exec_builtin(cur, global, &vars->fd, 1);
		exit(127);
	}
	else
	{
		if (check_redirection(cur, &vars->fd, global->data) == 0)
			child_pipes_process2(cur, global, sv, vars->fd);
		exit(127);
	}
}

static int	init(t_vars_4 *vars, t_global *global, t_token **cur)
{
	*cur = *(global->tokens);
	vars->fd = 1;
	vars->count = 0;
	if (set_exec_signals(global->data) == -1)
		return (0);
	global->pipes->fd1 = -1;
	global->pipes->fd2 = -1;
	vars->i = 0;
	vars->nbr = (*cur)->nbr_pipe;
	return (1);
}

static void	main_pipes2(t_global *global, t_vars_4 *vars, t_token *cur, int sv)
{
	pid_t	pid;

	while (vars->i < vars->nbr)
	{
		cur = global->tokens[vars->i];
		pipex(cur, global, sv);
		vars->count++;
		vars->i++;
	}
	cur = global->tokens[vars->i];
	vars->status = 0;
	pid = fork();
	if (pid == 0)
	{
		close(sv);
		child_process_main(vars, cur, global, sv);
	}
	else if (pid < 0)
		perror("fork");
	dup2(sv, STDIN_FILENO);
	close(sv);
	while (wait(&vars->status) != -1)
		;
	g_sigint_received = WEXITSTATUS(vars->status);
}

void	main_pipes(t_global *global)
{
	t_vars_4	vars;
	t_token		*cur;
	t_token		*cur_her;
	int			sv;

	sv = dup(STDIN_FILENO);
	if (!init(&vars, global, &cur))
		return ((void)close(sv));
	while (vars.i <= vars.nbr)
	{
		cur_her = global->tokens[vars.i];
		if (open_heredoc(cur_her, global, sv, vars.i) == -1)
			return ((void)close(sv));
		vars.i++;
	}
	vars.i = 0;
	main_pipes2(global, &vars, cur, sv);
}
