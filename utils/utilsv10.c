/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:59:09 by nadjemia          #+#    #+#             */
/*   Updated: 2024/08/16 23:06:03 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	supp_pipe(t_token **tokens, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (tokens[i])
			tokens[i]->nbr_pipe--;
		if (tokens[i] == NULL)
			break ;
		i++;
	}
	while (i < len)
	{
		tokens[i] = tokens[i + 1];
		if (tokens[i])
			tokens[i]->nbr_pipe--;
		i++;
	}
}

int	len_tokens(t_token **tokens)
{
	int		len;

	len = 0;
	while (tokens[len])
		len++;
	return (len);
}

int	there_is_cmd(t_token *list)
{
	t_token	*cur;

	cur = list;
	while (cur->prev)
		cur = cur->prev;
	while (cur)
	{
		if (cur->type == CMD)
			return (1);
		cur = cur->next;
	}
	return (0);
}

void	change_flag(int *error)
{
	*error = 1;
}
