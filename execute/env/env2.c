/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 01:43:37 by almichel          #+#    #+#             */
/*   Updated: 2024/04/28 01:44:19 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Fonction qui permet d'update la ligne OLDPWD de l'env a chaque fois que tu cd
void	update_oldpwd(t_list **env)
{
	t_list	*current;
	int		flag;
	char	*cwd;

	flag = 0;
	current = *env;
	cwd = get_actualpwd(env);
	if (cwd == NULL)
	{
		cwd = malloc((7) * sizeof(char));
		if (!cwd)
			return;
		ft_strcpy(cwd, "OLDPWD=", 7);
	}
	while (current)
	{
		if (strncmp(current->content, "OLDPWD=", 7) == 0)
		{
			flag = 1;
			free(current->content);
			current->content = cwd;
		}
		current = current->next;
	}
	add_back_oldpwd(flag, cwd, env);
}

void	add_back_oldpwd(int flag, char *cwd, t_list **env)
{
	t_list *new_case;
	
	if (flag == 0)
	{
		new_case = ft_lstnew(cwd);
		ft_lstadd_back(env, new_case);
	}
}
// Fonction qui m'aide pour update la ligne OLDPWD a chaque cd
char	*get_actualpwd(t_list **env)
{
	t_list	*current;
	char	*cwd;

	current = *env;
	while (current)
	{
		if (strncmp(current->content, "PWD=", 4) == 0)
		{
			cwd = malloc(((ft_strlen(current->content) + 4) * sizeof(char)));
			if (!cwd)
				return (NULL);
			ft_strcpy(cwd, "OLD", 3);
			cwd = ft_strcat(cwd, current->content);
			return (cwd);
		}
		current = current->next;
	}
	return (NULL);
}
