/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_pt2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:17:51 by noah              #+#    #+#             */
/*   Updated: 2024/09/05 12:15:53 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	rm(char *str, char quote, int in_quote)
{
	int	i;
	int	k;

	i = 0;
	if (str[i] == quote && !in_quote)
	{
		while (str[i] == quote)
		{
			k = i - 1;
			while (str[++k])
				str[k] = str[k + 1];
		}
	}
}

static void	rm_quotes(t_token *cur)
{
	int	i;
	int	in_single;
	int	in_double;

	i = -1;
	in_single = 0;
	in_double = 0;
	while (cur->content[++i])
	{
		is_in_quote(&in_single, &in_double, cur->content[i]);
		rm(&cur->content[i], '"', in_single);
		rm(&cur->content[i], '\'', in_double);
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
