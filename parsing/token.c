/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:15:55 by nadjemia          #+#    #+#             */
/*   Updated: 2024/05/21 14:38:56 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_token(t_token *list, t_type type, char *content)
{
	t_token	*cur;
	t_token	*new;
	
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->content = content;
	new->type = type;
	new->next = NULL;
	cur = list;
	if (!cur)
	{
		list = new;
		new->prev = NULL;
		return (1);
	}
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	new->prev = cur;
	return (1);
}

void	free_token(t_token **tokens)
{
	int	i;
	t_token	*cur;
	t_token	*rm;
	
	i = 0;
	while (tokens[i])
	{
		cur = tokens[i++];
		while (cur)
		{
			rm = cur;
			cur = cur->next;
			free(rm);
		}
	}
}