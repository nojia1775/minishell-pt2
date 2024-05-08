/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:20:52 by almichel          #+#    #+#             */
/*   Updated: 2024/04/30 19:46:00 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_dup2_one(t_pipes *pipes, int *end)
{
	if (dup2(end[1], STDOUT_FILENO) == -1)
	{
		ft_close_all(pipes);
		perror("dup2");
		return (-1);
	}
	return (1);
}

int	ft_dup2_two(t_pipes *pipes, int *end)
{
	if (dup2(end[0], STDIN_FILENO) == -1)
	{
		ft_close_all(pipes);
		perror("dup2");
		return (-1);
	}
	return (1);
}

void	ft_close_all(t_pipes *pipes)
{
	//if (pipes->flag1 == 0)
	//	close(pipes->fd1);
	close(pipes->fd2);
}
