/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:57:41 by almichel          #+#    #+#             */
/*   Updated: 2024/09/14 23:31:35 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// C'est l'inverse d'export,
//	tu peux supprimer des variables de l'env si tu fais par exemple unset PWD,
//	ca va supprimer la ligne pwd de ton env. cette fonction sert a ca
void	ft_unset(t_list **env, t_list **exp_var, char *var, t_data *data)
{
	t_list	**ptr;
	int		flag;
	t_list	*temp;

	(void)data;
	g_sigint_received = 0;
	ptr = env;
	flag = 0;
	while (*ptr)
	{
		if (ft_strncmp((*ptr)->content, var, ft_len_equal((*ptr)->content)
				- 1) == 0)
		{
			flag = 1;
			temp = *ptr;
			*ptr = temp->next;
			free(temp->content);
			free(temp);
		}
		else
			ptr = &(*ptr)->next;
	}
	if (exp_var && *exp_var)
		ft_unset2(flag, exp_var, var);
}

void	ft_unset2(int flag, t_list **exp_var, char *var)
{
	t_list	**ptr2;
	t_list	*temp2;

	ptr2 = exp_var;
	if (flag == 0)
	{
		while (*ptr2)
		{
			if (ft_strncmp((*ptr2)->content, var, ft_len_equal((*ptr2)->content)
					- 1) == 0)
			{
				temp2 = *ptr2;
				*ptr2 = temp2->next;
				free(temp2->content);
				free(temp2);
			}
			else
				ptr2 = &(*ptr2)->next;
		}
	}
}
