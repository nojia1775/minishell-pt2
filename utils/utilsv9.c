/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:01:38 by noah              #+#    #+#             */
/*   Updated: 2024/08/06 13:25:47 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*question_mark(char *str, long long code)
{
	char	*tmp;
	
	if (!ft_strncmp(str, "$?", 2))
	{
		tmp = ft_itoa((int)code);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	return (NULL);
}

static t_token	*supp(t_token *cur)
{
	t_token	*tmp;

	if (!cur->prev)
	{
		tmp = cur;
		cur = cur->next;
		cur->prev = NULL;
		free(tmp);
	}
	else if (!cur->next)
	{
		tmp = cur;
		cur->prev->next = NULL;
		cur = cur->prev;
		free(tmp);
	}
	else
	{
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
	return (cur);
}

void	supp_token(t_token **tokens)
{
	int		i;
	t_token	*cur;

	i = 0;
	while (tokens[i])
	{
		cur = tokens[i];
		while (cur)
		{
			if (!cur->content)
				cur = supp(cur);
			cur = cur->next;
		}
		i++;
	}
}

char	*get_cmd(t_token *token)
{
	t_token	*cur;

	cur = token;
	while (cur->prev)
		cur = cur->prev;
	return (cur->content);
}

char	*get_lim(t_token *cur)
{
	t_token	*token;
	
	if (!cur)
		return (NULL);
	token = cur;
	while (token->prev)
		token = token->prev;
	while (token->type != LIM && token)
		token = token->next;
	if (token)
		if (token->type == LIM)
			return (token->content);
	return (NULL);
}