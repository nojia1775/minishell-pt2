/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:46:58 by almichel          #+#    #+#             */
/*   Updated: 2024/08/09 15:44:30 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_token *cur, t_global *global)
{
	char **exit;
	
	exit = cur->cmd_pipex;
	ft_free_lists(&global->env, &global->exp_var);
	if (exit[1] == NULL)
	{
		free_double_tabs(exit);
		printf("exit\n");
		return ;
	}
	else if(exit[2] != NULL)
	{
		global->data->code = 1;
		free_double_tabs(exit);
		printf("exit\n");
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return;
	}
	ft_exit2(global->data, exit);
}

void	ft_exit2(t_data *data, char **exit)
{
	if (ft_is_digit(exit[1]) == -1 || ft_check_long(exit[1]) == -1)
	{
		data->code = 2;
		printf("exit\n");
		ft_putendl_fd("exit: numeric argument required", 2);
		free_double_tabs(exit);
		return;
	}
	else
	{
		printf("exit\n");
		data->code = ft_atoi_long(exit[1]) % 256;
		free_double_tabs(exit);
		return;
	}
}
