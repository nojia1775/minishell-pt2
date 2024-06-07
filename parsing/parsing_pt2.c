/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:13:22 by noah              #+#    #+#             */
/*   Updated: 2024/06/07 21:19:30 by noah             ###   ########.fr       */
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
	int i = 0;
	while (tokens[i])
	{	
		cur = tokens[i];
		while (cur)
		{
			printf("%d --- %s %d\n", i, cur->content, cur->type);
			cur = cur->next;
		}
		i++;
	}
	free_tokens(tokens);
	return (tokens);
}
