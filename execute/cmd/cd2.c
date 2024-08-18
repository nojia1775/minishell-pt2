/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 01:55:01 by almichel          #+#    #+#             */
/*   Updated: 2024/08/18 20:56:29 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Quand tu fais cd ~ ca te ramene a ton HOME, cette fonction permet de faire ca
void	ft_cd_home(t_global *global)
{
	global->data->path = NULL;
	get_home_path(global->data, &global->data->env);
	if (chdir(global->data->path) == 0)
	{
		global->data->pwd = getcwd(global->data->buf, sizeof(global->data->buf));
		free(global->data->total_setup);
		global->data->total_setup = init_lobby(global->data);
		update_env(&global->data->env);
		global->data->code = 0;
	}
	else
	{
		printf("cd: ~: No such file or directory \n");
		global->data->code = 1;
	}
}
