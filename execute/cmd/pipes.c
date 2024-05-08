/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <	almichel@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:04:29 by almichel          #+#    #+#             */
/*   Updated: 2024/05/08 13:59:19 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_pipes	init_struct(char *argv[], int i, int argc)
{
	t_pipes	pipes;

	pipes.flag1 = 0;
	pipes.cmd1 = argv[i];
	pipes.cmd2 = argv[argc - 3];
	pipes.fd1 = -1;
	pipes.fd2 = -1;
	pipes.status = NULL;
	pipes.good_line_envp = NULL;
	return (pipes);
}

void	init_fd2(char **argv, t_pipes *pipes, int argc)
{
	pipes->fd2 = open(argv[argc - 2], O_WRONLY | O_TRUNC, 0644);
	if (access(argv[argc - 2], W_OK) == -1 && access(argv[argc - 2], F_OK) == 0)
	{
		ft_putstr_fd_pipes(": Permission denied\n", 2, argv[argc - 2]);
		return;
	}
	if (pipes->fd2 < 0)
		pipes->fd2 = open(argv[argc - 2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(pipes->fd2, STDOUT_FILENO);
	close(pipes->fd2);
}

void	init_fd1(char **argv, t_pipes *pipes)
{
	if (access(argv[1], F_OK) != 0)
	{
		ft_putstr_fd_pipes(": No such file or directory\n", 2, argv[1]);
		pipes->flag1 = 1;
	}
	else
	{
		pipes->fd1 = open(argv[1], O_RDONLY);
		if (pipes->fd1 < 0)
			pipes->flag1 = 1;
		if (access(argv[1], R_OK) != 0)
			ft_putstr_fd_pipes(": Permission denied\n", 2, argv[1]);
		dup2(pipes->fd1, STDIN_FILENO);
		if (pipes->flag1 != 1)
			close(pipes->fd1);;
	}
}

void	pipex(t_pipes *pipes, char **envp)
{
	pid_t	pid;
	int		end[2];

	if (pipe(end) == -1)
		return ((perror("pipe")));
	pid = fork();
	if (pid == 0)
	{
		if (child_pipes_process1(pipes, envp, end) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	main_pipes(int argc, char *argv[], t_list **env, t_list **exp_var)
{
	t_pipes	pipes;
	int		i;
	int		count_cmd1;
	char 	**envp;

	envp = stock_total_env(env, exp_var);
	count_cmd1 = 0;
	i = 2;
	pipes = init_struct(argv, count_cmd1, argc);
	count_cmd1 = count_cmd1 + 2;
	init_fd1(argv, &pipes);
	init_fd2(argv, &pipes, argc);
	while (i < argc - 2)
	{	
		pipex(&pipes, envp);
		i++;
		pipes = init_struct(argv, count_cmd1, argc);
	}
	if (child_pipes_process2(&pipes, envp) == -1)
			exit(EXIT_FAILURE);
}
