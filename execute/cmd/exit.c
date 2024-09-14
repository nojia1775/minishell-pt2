/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:46:58 by almichel          #+#    #+#             */
/*   Updated: 2024/09/14 23:31:01 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	many_arg(t_token *cur)
{
	char	**exit;
	int		i;

	i = 0;
	exit = cur->cmd_pipex;
	if (!exit[1])
		return (1);
	if (exit[2] != NULL)
	{
		while (exit[1][i])
		{
			if (exit[1][i] >= '0' && exit[1][i] <= '9')
				i++;
			else
				return (1);
		}
		return (0);
	}
	return (1);
}

int	ft_no_exit(void)
{
	g_sigint_received = 1;
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	return (3);
}

int	ft_exit(t_token *cur, t_global *global)
{
	char	**exit;

	exit = cur->cmd_pipex;
	if (exit[1] == NULL)
	{
		free_all(global);
		printf("exit\n");
		return (0);
	}
	return (ft_exit2(global, exit));
}

int	ft_exit2(t_global *global, char **exit)
{
	long long	exit_code;

	if (ft_is_digit(exit[1]) == -1 || ft_check_long(exit[1]) == -1)
	{
		printf("exit\n");
		ft_putendl_fd("exit: numeric argument required", 2);
		free_all(global);
		return (2);
	}
	else
	{
		printf("exit\n");
		exit_code = ft_atoi_long(exit[1]) % 256;
		free_all(global);
		return (exit_code);
	}
}
