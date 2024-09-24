/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:29:57 by almichel          #+#    #+#             */
/*   Updated: 2024/09/24 15:51:03 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// je stock l'env de base au debut du programme dans une liste chainee
void	stock_env(char **env, t_list **envp)
{
	int		i;
	t_list	*new_case;

	if (!env)
		return ;
	i = 0;
	new_case = NULL;
	while (env[i])
	{
		new_case = ft_lstnew(ft_strdup(env[i]));
		ft_lstadd_back(envp, new_case);
		i++;
	}
}

//Fonction qui permet d'update la ligne PWD de l'env a chaque fois que tu cd
void	update_env(t_list **env)
{
	char	buf[1024];
	int		flag;
	t_list	*new_case;
	char	*new_content;
	char	*cwd;

	flag = 0;
	if (env != NULL)
	{
		update_oldpwd(env);
		find_pwd(&flag, env);
		if (flag == 0)
		{
			cwd = getcwd(buf, sizeof(buf));
			new_content = malloc(((ft_strlen(cwd) + 5) * sizeof(char)));
			ft_strlcpy(new_content, "PWD=", 5);
			ft_strcat(new_content, cwd);
			new_case = ft_lstnew(new_content);
			ft_lstadd_back(env, new_case);
		}
	}
}

void	find_pwd(int *flag, t_list **env)
{
	t_list	*current;
	char	*cwd;
	char	buf[1024];

	current = *env;
	while (current)
	{
		if (strncmp(current->content, "PWD=", 4) == 0)
		{
			*flag = 1;
			cwd = getcwd(buf, sizeof(buf));
			free(current->content);
			current->content = malloc(((ft_strlen(cwd) + 5) * sizeof(char)));
			current->content = ft_return_strcat("PWD=", cwd,
					current->content);
		}
		current = current->next;
	}
}

//Je print l'env
// envp correspond a l'env de base
// exp_var correpond aux variables que tu ajoutes via EXPORT
//les deux representent l'env donc je print les deux a chaque fois
// (ce sont des listes chainees qui contiennent un void * par node)
void	print_env(t_list **envp, t_list **exp_var, t_data *data)
{
	t_list	*top;
	t_list	*current;

	(void)data;
	current = *exp_var;
	top = *envp;
	if (envp != NULL)
	{
		while (top)
		{
			printf("%s\n", (char *)top->content);
			top = top->next;
		}
	}
	if (exp_var != NULL)
	{
		while (current)
		{
			printf("%s\n", (char *)current->content);
			current = current->next;
		}
	}
	g_sigint_received = 0;
}
