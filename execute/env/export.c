/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:10:18 by almichel          #+#    #+#             */
/*   Updated: 2024/09/05 12:14:17 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Quand tu rentres juste "export" dans le shell,
//	ca print ton env par ordre alphabetique et ca rajoute "declare -x",
//	cette fonction permet de faire ca
void	ft_export(t_list **env, t_list **exp_var)
{
	int		i;
	t_list	*current;
	t_list	*head;
	char	**export;

	head = *exp_var;
	current = *env;
	i = 0;
	if (!env)
	{
		printf("env: «export»: Aucun fichier ou dossier de ce type\n");
		return ;
	}
	i = ft_lstlen(env);
	if (exp_var != NULL)
		i = i + ft_lstlen(exp_var);
	export = malloc((i + 1) * sizeof(char *));
	if (!export)
		return ;
	export[i] = NULL;
	i = 0;
	add_declare_x(export, current, env, &i);
	add_declare_x(export, head, exp_var, &i);
	trie_export(export, i);
	print_export(export);
}

void	add_declare_x(char **export, t_list *current, t_list **list, int *i)
{
	current = *list;
	if (list)
	{
		while (current)
		{
			export[*i] = malloc(ft_strlen(current->content) + 12);
			ft_strcpy_wn(export[*i], "declare -x ", 12);
			ft_strcat(export[*i], current -> content);
			current = current->next;
			*i = *i + 1;
		}
	}
}

void	trie_export(char **export, int i)
{
	char	*temp;
	int		max;
	int		j;

	max = i;
	i = 0;
	while (i < max - 1)
	{
		j = 0;
		while (j < max - 1)
		{
			if (strcmp(export[j], export[j + 1]) > 0)
			{
				temp = export[j];
				export[j] = export[j + 1];
				export[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_export(char **export)
{
	int	i;

	i = 0;
	if (export)
	{
		while (export[i])
			printf("%s\n", export[i++]);
		free_double_tabs(export);
	}
}
