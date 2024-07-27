/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:04:29 by almichel          #+#    #+#             */
/*   Updated: 2024/07/27 19:07:35 by almichel         ###   ########.fr       */
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

void	pipex(t_token *cur, t_pipes *pipes, char **envp, t_data *data, int count)
{
	pid_t	pid;
	int		end[2];
	int		fd;

	fd = -1;
	count = count + 0;
	data->code = 0;
	if (pipe(end) == -1)
		return ((perror("pipe")));
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
		if (check_redirection(cur, &fd) == 0)
			child_pipes_process1(cur, pipes, envp, fd);
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

void	main_pipes(t_token **input_tokenised, char **envp, t_data *data)
{
	t_pipes	pipes;
	int		i;
	int		count;
	int		sv;
	int		status;
	pid_t	pid;
	int		fd;
	t_token *cur;

	cur = *input_tokenised;

	fd = -1;
	count = 0;

	sv = dup(STDIN_FILENO);
	pipes.fd1 = -1;
	pipes.fd2 = -1;
	envp = envp + 0;
	data->code = data->code + 0;
	i = 0;
	int nbr = cur->nbr_pipe;
	while (i < nbr)
	{
		cur = input_tokenised[i];
		pipex(cur, &pipes, envp, data, count);
		count++;
		i++;
	}
	fd = -1;
	status = 0;
	cur = input_tokenised[i++];
	pid = fork();
	if (pid == 0)
	{
		data->code = 0;
		if (check_redirection(cur, &fd) == 0)
			child_pipes_process2(cur, &pipes, envp, sv, fd);
		exit(127);
	}
	else if (pid > 0)
	{
		status = status + 0;
	}
	else
		perror("fork");
	dup2(sv, STDIN_FILENO);
	while (wait(&status) != -1);
	data->code = WEXITSTATUS(status);
}
