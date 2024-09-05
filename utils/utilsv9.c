/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:01:38 by noah              #+#    #+#             */
/*   Updated: 2024/08/30 22:50:31 by noah             ###   ########.fr       */
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
		if (cur)
			cur->prev = NULL;
	}
	else if (!cur->next)
	{
		tmp = cur;
		cur->prev->next = NULL;
		cur = cur->prev;
	}
	else
	{
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		tmp = cur;
		cur = cur->next;
	}
	free(tmp);
	return (cur);
}

void	supp_token(t_token **tokens)
{
	int		i;
	int		len;
	t_token	*cur;

	i = 0;
	while (tokens[i])
	{
		cur = tokens[i];
		len = len_tokens(tokens);
		while (cur)
		{
			if (!cur->content || !cur->content[0])
			{
				if (cur == tokens[i])
					tokens[i] = cur->next;
				cur = supp(cur);
			}
			else
				cur = cur->next;
		}
		if (tokens[i] == NULL)
			supp_pipe(tokens, len);
		else
			i++;
	}
}

char	*get_cmd(t_token *token)
{
	t_token	*cur;
	char	*tmp;

	cur = token;
	while (cur->prev)
		cur = cur->prev;
	tmp = cur->content;
	while (cur)
	{
		if (cur->type == CMD)
			return (cur->content);
		cur = cur->next;
	}
	return (tmp);
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
