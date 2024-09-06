/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:04:29 by almichel          #+#    #+#             */
/*   Updated: 2024/09/06 23:53:32 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	child_process_pipex(int *end, int *fd, t_global *global,
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
			exec_builtin(cur, global, *fd, 1);
		exit(127);
	}
	if (check_redirection(cur, fd, global->data) == 0)
		child_pipes_process1(cur, global->pipes, global->data->envv, *fd);
	exit(127);
}

int	pipex(t_token *cur, t_global *global)
{
	pid_t	pid;
	int		end[2];
	int		fd;

	fd = -1;
	global->data->code = 0;
	if (pipe(end) == -1)
		perror("pipe");
	pid = fork();
	if (pid == 0)
		child_process_pipex(end, &fd, global, cur);
	else if (pid > 0)
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		close(end[0]);
	}
	else
		perror("fork");
	return (0);
}

typedef struct s_vars
{
	int	i;
	int	count;
	int	status;
	int	fd;
	int	sv;
	int	nbr;
}	t_vars;

static void	child_process_main(t_vars *vars, t_token *cur, t_global *global)
{
	if (is_a_builtin(get_cmd(cur)) == 1)
	{
		if (check_redirection(cur, &vars->fd, global->data) == 0)
			exec_builtin(cur, global, vars->fd, 1);
		exit(127);
	}
	else
	{
		if (check_redirection(cur, &vars->fd, global->data) == 0)
			child_pipes_process2(cur, global, vars->sv, vars->fd);
		exit(127);
	}
}

static int	init(t_vars *vars, t_global *global, t_token **cur)
{
	vars->sv = dup(STDIN_FILENO);
	*cur = *(global->tokens);
	vars->fd = -1;
	vars->count = 0;
	if (set_exec_signals(global->data) == -1)
		return (0);
	global->pipes->fd1 = -1;
	global->pipes->fd2 = -1;
	vars->i = 0;
	vars->nbr = (*cur)->nbr_pipe;
	return (1);
}

void	main_pipes(t_global *global)
{
	t_vars	vars;
	pid_t	pid;
	t_token	*cur;

	if (!init(&vars, global, &cur))
		return ;
	while (vars.i < vars.nbr)
	{
		cur = global->tokens[vars.i];
		pipex(cur, global);
		vars.count++;
		vars.i++;
	}
	cur = global->tokens[vars.i];
	vars.fd = -1;
	vars.status = 0;
	pid = fork();
	if (pid == 0)
		child_process_main(&vars, cur, global);
	else if (pid < 0)
		perror("fork");
	dup2(vars.sv, STDIN_FILENO);
	while (wait(&vars.status) != -1)
		;
	global->data->code = WEXITSTATUS(vars.status);
}
