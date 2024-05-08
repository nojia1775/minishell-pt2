/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 00:47:08 by almichel          #+#    #+#             */
/*   Updated: 2024/04/28 00:47:45 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Si tu tapes par exemple "export a=12" dans le shell,
//	ca va ajouter la variable a=12 a l'env, cette fonction permet de faire ca

void	export_variable(t_list **env, t_list **exp_var, char *var, t_code *code)
{
	t_list	*current;
	int		flag;
	t_list	*new_case;
	t_list	*head;

	if (exp_var)
		head = *exp_var;
	flag = 0;
	if (ft_check_equal(var) == -1)
	{
		code->code = 1;
		return ;
	}
	code->code = 0;
	current = *env;
	export_variable2(current, env, &flag, var);
	export_variable2(head, exp_var, &flag, var);
	if (flag == 0)
	{
		new_case = ft_lstnew(var);
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
				current->content = var;
			}
			current = current->next;
		}
	}
}
