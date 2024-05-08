/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:10:18 by almichel          #+#    #+#             */
/*   Updated: 2024/04/28 00:55:03 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Quand tu rentres juste "export" dans le shell,
//	ca print ton env par ordre alphabetique et ca rajoute "declare -x",
//	cette fonction permet de faire ca
void	ft_export(t_data *data, t_list **env, t_list **exp_var)
{
	int		i;
	t_list	*current;
	t_list	*head;

	head = *exp_var;
	current = *env;
	i = 0;
	if (!env)
	{
		ft_printf("env: «export»: Aucun fichier ou dossier de ce type\n");
		return;
	}
	i = ft_lstlen(env);
	if (exp_var != NULL)
		i = i + ft_lstlen(exp_var);
	data->export = malloc((i + 1) * sizeof(char *));
	if (!data->export)
		return ;
	data->export[i] = NULL;
	i = 0;
	add_declare_x(data, current, env, &i);
	add_declare_x(data, head, exp_var, &i);
	trie_export(data, i);
	print_export(data);
}

void	add_declare_x(t_data *data, t_list *current, t_list **list, int *i)
{
	current = *list;
	if (list)
	{
		while (current)
		{
			data->export[*i] = malloc(ft_strlen(current->content) + 12);
			ft_strcpy_wn(data->export[*i], "declare -x ", 12);
			ft_strcat(data->export[*i], current -> content);
			current = current->next;
			*i = *i + 1;
		}
	}
}

void	trie_export(t_data *data, int i)
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
			if (strcmp(data->export[j], data->export[j + 1]) > 0)
			{
				temp = data->export[j];
				data->export[j] = data->export[j + 1];
				data->export[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_export(t_data *data)
{
	int	i;

	i = 0;
	if (data->export)
	{
		while (data->export[i])
			ft_printf("%s\n", data->export[i++]);
		free_double_tabs(data->export);
	}
}


