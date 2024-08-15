/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:04:29 by almichel          #+#    #+#             */
/*   Updated: 2024/08/15 12:45:20 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			if (check_redirection(cur, &fd, global->data) == 0)
				exec_builtin(cur, global, fd);
			exit(127);
		}
		if (check_redirection(cur, &fd, global->data) == 0)
			child_pipes_process1(cur, global->pipes, global->envv, fd);
		exit(127);
	}
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

void	main_pipes(t_global *global)
{
	int		i;
	int		count;
	int		status;
	pid_t	pid;
	int		fd;
	t_token *cur;

	int		sv;

	sv = dup(STDIN_FILENO);
	cur = *(global->tokens); 
	fd = -1;
	count = 0;

	if (set_exec_signals(global->data) == -1)
		return;
	global->pipes->fd1 = -1;
	global->pipes->fd2 = -1;
	i = 0;
	printf("+++ %d\n", cur->nbr_pipe);
	int nbr = cur->nbr_pipe;
	while (i < nbr)
	{
		cur = global->tokens[i];
		pipex(cur, global);
		count++;
		i++;
	}
	cur = global->tokens[i];
	fd = -1;
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (is_a_builtin(get_cmd(cur)) == 1)
		{
			if (check_redirection(cur, &fd, global->data) == 0)
				exec_builtin(cur, global, fd);
			exit (127);
		}
		else
		{
			if (check_redirection(cur, &fd, global->data) == 0)
				child_pipes_process2(cur, global, sv, fd);
			exit(127);
		}
	}
	else if (pid < 0)
		perror("fork");
	dup2(sv, STDIN_FILENO);
	while (wait(&status) != -1);
	global->data->code = WEXITSTATUS(status);
}
