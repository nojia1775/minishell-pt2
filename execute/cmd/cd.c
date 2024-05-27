/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 00:05:45 by almichel          #+#    #+#             */
/*   Updated: 2024/05/27 03:28:06 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Fonction principale de cd,
//  A chaque cd, je dois update le dossier dans le quel on se trouve
// la fonction update_env que j'appelle permet d'update la ligne PWD et OLDPWD de l'env a chaque cd
void	ft_cd(t_data *data, t_list **env)
{
	int	flag;

	char **tab;
	
	
	tab = ft_split(data->str, ' ');
	if (ft_strlen_double_tab(tab) >= 3)
	{
		free_double_tabs(tab);
		ft_putendl_fd("cd: too many arguments", 2);
		data->code = 1;
		return;
	}
	flag = 0;
	data->path = tab[1];
	ft_cd2(flag, env, data);
	free_double_tabs(tab);
}

void	ft_cd2(int flag, t_list **env, t_data *data)
{
	char *join1;
	char *join2;
	
//	printf("%s\n",data->path);
	if (chdir(data->path) == 0)
	{
		data->pwd = getcwd(data->buf, sizeof(data->buf));
		free(data->total_setup);
		data->total_setup = init_lobby(data);
		update_env(env);
		if (flag == 1)
			free(data->path);
		data->code = 0;
	}
	else
	{
		data->code = 1;
		if (flag == 1)
			free(data->path);
		join1 = ft_strjoin("cd: ", data->str + 3);
		join2 = ft_strjoin(join1, ": No such file or directory");
		ft_putendl_fd(join2, 2);
		free(join1);
		free(join2);
	}
}
// J'extrais la variable Home de mon env pour la donner a la fonction au dessus
void	get_home_path(t_data *data, t_list **env)
{
	t_list	*current;

	current = *env;
	while (current)
	{
		if (ft_strncmp("HOME=", current->content, 5) == 0)
			data->path = current->content + 5;
		current = current->next;
	}
}
