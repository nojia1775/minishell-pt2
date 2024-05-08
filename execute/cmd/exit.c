/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:46:58 by almichel          #+#    #+#             */
/*   Updated: 2024/04/27 23:54:45 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(char *str, t_list **env, t_list **exp_var, t_code *code)
{
	char **exit;
	
	exit = ft_split(str, ' ');
	ft_free_lists(env, exp_var);
	if (exit[1] == NULL)
	{
		free_double_tabs(exit);
		ft_printf("exit\n");
		return;
	}
	else if(exit[2] != NULL)
	{
		code->code = 1;
		free_double_tabs(exit);
		ft_printf("exit\n");
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return;
	}
	ft_exit2(code, exit);
}

void	ft_exit2(t_code *code, char **exit)
{
	if (ft_is_digit(exit[1]) == -1 || ft_check_long(exit[1]) == -1)
	{
		code->code = 2;
		ft_printf("exit\n");
		ft_putendl_fd("exit: numeric argument required", 2);
		free_double_tabs(exit);
		return;
	}
	else
	{
		ft_printf("exit\n");
		code->code = ft_atoi_long(exit[1]) % 256;
		free_double_tabs(exit);
		return;
	}
}
