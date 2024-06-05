/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:13:22 by noah              #+#    #+#             */
/*   Updated: 2024/06/04 13:34:38 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	**parsing_pt2(char *input, t_list **env, t_list **exp_var)
{
	t_token	**tokens;
	t_token	*cur;
	
	if (input[0] == '\0')
		return (NULL);
	if (!conform_redir(input))
		return (printf("minishell : syntax error near unexpected token `>'\n"), NULL);
	if (!conform_pipe(input))
		return (printf("minishell : Syntax error\n"), NULL);
	tokens = tokenisation(input, env, exp_var);
	cur = tokens[0];
	while (cur)
	{
		printf("--- %s\n", cur->content);
		cur = cur->next;
	}
	return (tokens);
}
