/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 00:05:45 by almichel          #+#    #+#             */
/*   Updated: 2024/09/18 10:04:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_oldpwd(t_list *env)
{
	t_list	*cur;

	cur = env;
	while (cur)
	{
		if (!ft_strncmp(cur->content, "OLDPWD=", 7))
			return (cur->content + 7);
		cur = cur->next;
	}
	return (NULL);
}

// Fonction principale de cd,
//  A chaque cd, je dois update le dossier dans le quel on se trouve
// la fonction update_env que j'appelle permet d'update la ligne
// PWD et OLDPWD de l'env a chaque cd
void	ft_cd(t_token *cur, t_global *global)
{
	int		flag;
	char	**tab;

	tab = cur->cmd_pipex;
	if (ft_strlen_double_tab(tab) >= 3)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		g_sigint_received = 1;
		return ;
	}
	flag = 0;
	if (ft_strlen_double_tab(tab) == 1)
		return (ft_cd_home(global));
	else if (!ft_strcmp(tab[1], "-"))
	{
		global->data->path = get_oldpwd(global->data->env);
		printf("%s\n", global->data->path);
	}
	else if (!ft_strcmp(tab[1], "~"))
		return (ft_cd_home(global));
	else
		global->data->path = tab[1];
	ft_cd2(flag, global);
}

void	ft_cd2(int flag, t_global *global)
{
	char	*join1;
	char	*join2;

	if (chdir(global->data->path) == 0)
	{
		global->data->pwd = getcwd(global->data->buf,
				sizeof(global->data->buf));
		free(global->data->total_setup);
		init_lobby(global->data);
		update_env(&global->data->env);
		if (flag == 1)
			free(global->data->path);
		g_sigint_received = 0;
	}
	else
	{
		g_sigint_received = 1;
		if (flag == 1)
			free(global->data->path);
		join1 = ft_strjoin("cd: ", global->cur->next->content);
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
