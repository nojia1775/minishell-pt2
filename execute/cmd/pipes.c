/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:04:29 by almichel          #+#    #+#             */
/*   Updated: 2024/05/13 15:48:28 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_struct(char *argv[], int i, int argc, t_pipes *pipes)
{
	pipes->flag1 = 0;
	pipes->cmd1 = argv[i];
	pipes->cmd2 = argv[argc - 3];
	//	pipes.fd1 = -1;
	//	pipes.fd2 = -1;
	pipes->status = NULL;
	pipes->good_line_envp = NULL;
}

void	init_fd2(char **argv, t_pipes *pipes, int argc)
{
	pipes->fd2 = open(argv[argc - 2], O_WRONLY | O_TRUNC, 0644);
	if (access(argv[argc - 2], W_OK) == -1 && access(argv[argc - 2], F_OK) == 0)
	{
		ft_putstr_fd_pipes(": Permission denied\n", 2, argv[argc - 2]);
		return ;
	}
	if (pipes->fd2 < 0)
		pipes->fd2 = open(argv[argc - 2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
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
	}
	// if (pipes->flag1 != 1)
	//		close(pipes->fd1);
}

void	pipex(t_pipes *pipes, char **envp, t_code *code, int count)
{
	pid_t	pid;
	int		end[2];

	//	int 	status;
	// status = 0;
	count = count + 0;
	code->code = 0;
	if (pipe(end) == -1)
		return ((perror("pipe")));
	pid = fork();
	if (pid == 0)
	{
		close(end[0]);
		dup2(end[1], STDOUT_FILENO);
		close(end[1]);
		//	if (count == 0)
		//	{
		//		dup2(pipes->fd1, STDIN_FILENO);
		//		close(pipes->fd1);
		//	}
		child_pipes_process1(pipes, envp);
		exit(127);
	}
	else if (pid > 0)
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		close(end[0]);
		//	waitpid(pid, &status, 0);
		//	if (WIFEXITED(status))
		//		code->code = WEXITSTATUS(status);
	}
	else
		perror("fork");
}

void	main_pipes(int argc, char *argv[], char **envp, t_code *code,
		char *data_str)
{
	t_pipes	pipes;
	int		i;
	int		count_cmd1;
	int		count;
	int		sv;
	int		status;
	pid_t	pid;

	count = 0;
	// i = 0;
	// ft_printf("%d\n", argc);
	// while(argv[i])
	//	printf("%s\n", argv[i++]);
	sv = dup(STDIN_FILENO);
	pipes.fd1 = -1;
	pipes.fd2 = -1;
	envp = envp + 0;
	code = code + 0;
	count_cmd1 = 0;
	(void)data_str;
	i = 2;
	i = i + 0;
	init_struct(argv, count_cmd1, argc, &pipes);
	count_cmd1 = count_cmd1 + 2;
	init_fd1(argv, &pipes);
	while (i < argc - 2)
	{
		pipex(&pipes, envp, code, count);
		count++;
		i++;
		init_struct(argv, count_cmd1, argc, &pipes);
	}
	init_fd2(argv, &pipes, argc);
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		code->code = 0;
		dup2(pipes.fd2, STDOUT_FILENO);
		close (pipes.fd2);
		child_pipes_process2(&pipes, envp);
		exit(127);
	}
	else if (pid > 0)
	{
		// waitpid(pid, &status, 0);
		//	if (WIFEXITED(status))
		//	code->code = WEXITSTATUS(status);
		status = status + 0;
	}
	else
		perror("fork");
	dup2(sv, STDIN_FILENO);
	while (wait(&status) != -1);
	code->code = WEXITSTATUS(status);
}
