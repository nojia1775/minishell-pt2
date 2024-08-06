/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:52:16 by noah              #+#    #+#             */
/*   Updated: 2024/08/06 14:02:45 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redir(t_token *cur);

static void	heredoc_type(t_token *cur)
{
	cur->type = HEREDOC;
	cur->next->type = LIM;
	if (cur->next->next && !is_redir(cur))
		cur->next->next->type = CMD;
}

static int	is_redir(t_token *cur)
{
	if (!ft_strcmp(cur->content, "<<") && cur->type == -1)
		heredoc_type(cur);
	else if (!ft_strcmp(cur->content, "<") && cur->type == -1)
	{
		cur->type = OUTREDIR;
		if (cur->next->next)
			cur->next->next->type = CMD;
	}
	else if (!ft_strcmp(cur->content, ">") && cur->type == -1)
		cur->type = INREDIR;
	else if (!ft_strcmp(cur->content, ">>") && cur->type == -1)
		cur->type = INREDIRAPP;
	else
		return (0);
	return (1);
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
			is_redir(cur);
			if (!cur->prev && cur->type == -1)
				cur->type = CMD;
			if (is_opt(cur) && cur->type == -1)
				cur->type = OPT;
			if (cur->type == -1)
				cur->type = ARG;
			cur = cur->next;
		}
	}
}