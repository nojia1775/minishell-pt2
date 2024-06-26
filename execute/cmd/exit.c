/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:46:58 by almichel          #+#    #+#             */
/*   Updated: 2024/05/26 03:34:36 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_data *data, t_list **env, t_list **exp_var)
{
	char **exit;
	
	exit = ft_split(data->str, ' ');
	ft_free_lists(env, exp_var);
	if (exit[1] == NULL)
	{
		free_double_tabs(exit);
		ft_printf("exit\n");
		return;
	}
	else if(exit[2] != NULL)
	{
		data->code = 1;
		free_double_tabs(exit);
		ft_printf("exit\n");
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return;
	}
	ft_exit2(data, exit);
}

void	ft_exit2(t_data *data, char **exit)
{
	if (ft_is_digit(exit[1]) == -1 || ft_check_long(exit[1]) == -1)
	{
		data->code = 2;
		ft_printf("exit\n");
		ft_putendl_fd("exit: numeric argument required", 2);
		free_double_tabs(exit);
		return;
	}
	else
	{
		ft_printf("exit\n");
		data->code = ft_atoi_long(exit[1]) % 256;
		free_double_tabs(exit);
		return;
	}
}
