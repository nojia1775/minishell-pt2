/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:46:58 by almichel          #+#    #+#             */
/*   Updated: 2024/08/18 20:56:44 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(t_token *cur, t_global *global)
{
	char **exit;
	
	exit = cur->cmd_pipex;
	ft_free_lists(&global->data->env, &global->data->exp_var);
	if (exit[1] == NULL)
	{
		//free_double_tabs(exit);
		free_all(global);
		printf("exit\n");
		return (0);
	}
	else if(exit[2] != NULL)
	{
		//free_double_tabs(exit);
		free_all(global);
		printf("exit\n");
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (2);
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
