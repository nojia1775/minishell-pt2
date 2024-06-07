/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:52:16 by noah              #+#    #+#             */
/*   Updated: 2024/06/07 19:16:53 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			if (cur->prev == NULL
				&& !ft_strcmp(cur->content, "<<"))
				cur->type = HEREDOC;
			else if (cur->prev && cur->prev->type == HEREDOC)
				cur->type = LIM;
			else if (cur->prev && cur->prev->type == LIM)
				cur->type = CMD;
			else
				cur->type = WORD;
			cur = cur->next;
		}
	}
}
