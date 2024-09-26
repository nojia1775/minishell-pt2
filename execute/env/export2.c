/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 00:47:08 by almichel          #+#    #+#             */
/*   Updated: 2024/09/26 14:27:19 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Si tu tapes par exemple "export a=12" dans le shell,
//	ca va ajouter la variable a=12 a l'env, cette fonction permet de faire ca
void	export_variable(t_list **env, t_list **exp_var, char *var, t_data *data)
{
	t_list	*current;
	int		flag;
	t_list	*new_case;
	t_list	*head;

	(void)data;
	if (exp_var)
		head = *exp_var;
	flag = 0;
	if (ft_check_equal(var) == -1)
	{
		g_sigint_received = 1;
		return ;
	}
	g_sigint_received = 0;
	current = *env;
	export_variable2(current, env, &flag, var);
	export_variable2(head, exp_var, &flag, var);
	if (flag == 0 || flag == 2)
	{
		new_case = ft_lstnew(ft_strdup(var));
		ft_lstadd_back(exp_var, new_case);
	}
}

void	export_variable2(t_list *current, t_list **list, int *flag, char *var)
{
	if (list && *flag == 0)
	{
		while (current)
		{
			if (ft_strncmp(current->content, var, ft_len_equal(var)) == 0)
			{
				*flag = 1;
				free(current->content);
				current->content = ft_strdup(var);
				if (!current->content)
				{
					*flag = 0;
					return ;
				}
			}
			current = current->next;
		}
	}
}
