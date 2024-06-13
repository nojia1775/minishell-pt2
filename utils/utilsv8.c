/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:06:56 by noah              #+#    #+#             */
/*   Updated: 2024/06/13 18:39:47 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_in_quote(int *in_single, int *in_double, char c)
{
	if (c == '"' && !(*in_single))
		*in_double = !(*in_double);
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
}

// free les tokens et leurs membres
void	free_tokens(t_token **tokens)
{
	t_token	*cur;
	t_token	*rm;
	int		i;
		
	i = 0;
	cur = tokens[i];
	while (tokens[i])
	{
		while (cur)
		{
			rm = cur;
			free(cur->content);
			cur = cur->next;
			free(rm);
		}
		i++;
	}
	free(tokens);
}

// ajoute un token à la liste chainée
int	add_token(t_token **tokens, char *content)
{
	t_token	*cur;
	t_token	*new;

	if (!content[0])
		return (1);
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->content = ft_strdup(content);
	new->next = NULL;
	cur = *tokens;
	if (!cur)
	{
		new->prev = NULL;
		*tokens = new;
	}
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new;
		new->prev = cur;
	}
	return (1);
}