/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 01:55:01 by almichel          #+#    #+#             */
/*   Updated: 2024/04/28 01:55:19 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Quand tu fais cd ~ ca te ramene a ton HOME, cette fonction permet de faire ca
void	ft_cd_home(t_data *data, t_list **env)
{
	data->path = NULL;
	get_home_path(data, env);
	if (chdir(data->path) == 0)
	{
		data->pwd = getcwd(data->buf, sizeof(data->buf));
		free(data->total_setup);
		data->total_setup = init_lobby(data);
		update_env(env);
	}
	else
		ft_printf("cd: ~: No such file or directory \n");
}
