/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 19:20:52 by almichel          #+#    #+#             */
/*   Updated: 2024/08/27 16:57:58 by nadjemia         ###   ########.fr       */
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
	close(pipes->fd2);
}
