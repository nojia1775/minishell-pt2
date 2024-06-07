/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_pt2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:17:51 by noah              #+#    #+#             */
/*   Updated: 2024/06/07 22:32:27 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	rm_quotes(t_token *cur)
{
	int	i;
	int	in_single;
	int	in_double;
	int	k;
	
	i = -1;
	in_single = 0;
	in_double = 0;
	while (cur->content[++i])
	{
		is_in_quote(&in_single, &in_double, cur->content[i]);
		if (cur->content[i] == '"' && !in_single)
		{
			k = i - 1;
			while (cur->content[++k])
				cur->content[k] = cur->content[k + 1];
		}
		if (cur->content[i] == '\'' && !in_double)
		{
			k = i - 1;
			while (cur->content[++k])
				cur->content[k] = cur->content[k + 1];
		}
	}
}

void	quotes(t_token **tokens)
{
	t_token	*cur;
	int		i;

	i = 0;
	while (tokens[i])
	{
		cur = tokens[i];
		while (cur)
		{
			rm_quotes(cur);
			cur = cur->next;
		}
		i++;
	}
}