/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv13.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:02:12 by nadjemia          #+#    #+#             */
/*   Updated: 2024/09/14 23:23:29 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	thereis_heredoc(t_token *token)
{
	t_token	*cur;

	cur = token;
	while (cur)
	{
		if (cur->type == HEREDOC)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	pipex(t_token *cur, t_global *global)
{
	pid_t	pid;
	int		end[2];
	int		fd;

	fd = -1;
	g_sigint_received = 0;
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

int	set_interactive_signals_hd(t_global *global)
{
	(void)global;
	if (signal(SIGINT, signal_handler_hd) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	return (1);
}
