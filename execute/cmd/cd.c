/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 00:05:45 by almichel          #+#    #+#             */
/*   Updated: 2024/05/08 15:42:47 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Fonction principale de cd,
//  A chaque cd, je dois update le dossier dans le quel on se trouve
// la fonction update_env que j'appelle permet d'update la ligne PWD et OLDPWD de l'env a chaque cd
void	ft_cd(t_data *data, t_list **env, t_list **exp_var, t_code *code)
{
	int	flag;

	char **tab;
	
	
	tab = ft_split(data->str, ' ');
	if (tab[2] != NULL)
	{
		free_double_tabs(tab);
		ft_putendl_fd("cd: too many arguments", 2);
		code->code = 1;
		return;
	}
	free_double_tabs(tab);
	flag = 0;
	data->path = data->str + 3;
	if (find_var_cd(data->path + 1, env, exp_var) == 0)
	{
		flag = 1;
		data->path = put_path_cd(data->path + 1, env, exp_var);
	}
	ft_cd2(code, flag, env, data);
}

void	ft_cd2(t_code *code, int flag, t_list **env, t_data *data)
{
	char *join1;
	char *join2;
	
	if (chdir(data->path) == 0)
	{
		data->pwd = getcwd(data->buf, sizeof(data->buf));
		free(data->total_setup);
		data->total_setup = init_lobby(data);
		update_env(env);
		if (flag == 1)
			free(data->path);
		code->code = 0;
	}
	else
	{
		code->code = 1;
		if (flag == 1)
			free(data->path);
		join1 = ft_strjoin("cd: ", data->str + 3);
		join2 = ft_strjoin(join1, ": No such file or directory");
		ft_putendl_fd(join2, 2);
		free(join1);
		free(join2);
	}
}
// On peut faire un cd $HOME par exemple, donc je cherche si ya la commande de cd correspond a une variable de l'env
int	find_var_cd(char *path, t_list **env, t_list **exp_var)
{
	t_list	*current;
	t_list	*head;

	current = *env;
	head = *exp_var;
	if (env && *env)
	{
		while (current)
		{
			if (ft_strncmp(path, current->content, ft_strlen(path)) == 0)
				return (0);
			current = current->next;
		}
	}
	if (exp_var && *exp_var)
	{
		while (head)
		{
			if (ft_strncmp(path, head->content, ft_strlen(path)) == 0)
				return (0);
			head = head->next;
		}
	}
	return (-1);
}

// si la variable est trouvee, je stock le chemin associe
char	*put_path_cd(char *path, t_list **env, t_list **exp_var)
{
	t_list	*current;
	t_list	*head;

	current = *env;
	head = *exp_var;
	if (env && *env)
	{
		while (current)
		{
			if (ft_strncmp(path, current->content, ft_strlen(path)) == 0)
				return (path = ft_strdup(current->content + 1 + ft_strlen(path)));
			current = current->next;
		}
	}
	if (exp_var && *exp_var)
	{
		while (head)
		{
			if (ft_strncmp(path, head->content, ft_strlen(path)) == 0)
				return (path = ft_strdup(head->content + ft_strlen(path)));
			head = head->next;
		}
	}
	return (NULL);
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
