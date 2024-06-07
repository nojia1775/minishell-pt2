/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:52:16 by noah              #+#    #+#             */
/*   Updated: 2024/06/07 22:10:16 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	assigned(t_token *cur)
{
	if (cur->type < WORD || cur->type > OPT)
		return (0);
	return (1);
}

static void	heredoc_type(t_token *cur)
{
	cur->type = HEREDOC;
	cur->next->type = LIM;
	if (cur->next->next)
		cur->next->next->type = CMD;
}

static int	is_opt(t_token *cur)
{
	if (cur->prev == NULL)
		return (0);
	if (cur->prev->type != CMD)
		return (0);
	if (cur->content[0] == '-' && ft_isalpha(cur->content[1]))
		return (1);
	return (0);
}

void	type_token(t_token **tokens)
{
	t_token	*cur;
	int		i;
	
	i = -1;
	while (tokens[++i])
	{
		cur = tokens[i];
		while (cur)
		{
			if (!ft_strcmp(cur->content, "<<") && !assigned(cur))
				heredoc_type(cur);
			if (!ft_strcmp(cur->content, "<") && !assigned(cur))
				cur->type = OUTREDIR;
			if (!ft_strcmp(cur->content, ">") && !assigned(cur))
				cur->type = INREDIR;
			if (!cur->prev && !assigned(cur))
				cur->type = CMD;
			if (is_opt(cur) && !assigned(cur))
				cur->type = OPT;
			if (!assigned(cur))
				cur->type = WORD;
			cur = cur->next;
		}
	}
}
