/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:13:22 by noah              #+#    #+#             */
/*   Updated: 2024/07/24 14:19:27 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	**parsing_pt2(char *input, t_list **env, t_list **exp_var)
{
	t_token	**tokens;
	t_token	*cur;
	
	if (input[0] == '\0')
		return (NULL);
	if (!nbr_quotes(input))
		return (printf("minishell : syntax error\n"), NULL);
	if (!conform_redir(input))
		return (printf("minishell : syntax error near unexpected token `>'\n"), NULL);
	if (!conform_pipe(input))
		return (printf("minishell : Syntax error\n"), NULL);
	tokens = tokenisation(input, env, exp_var);
	int i = 0;
	while (tokens[i])
	{	
		cur = tokens[i];
		if (cur->redir)
		{
			int j = 0;
			while (cur->redir[j])
				printf("+++ %s\n", cur->redir[j++]);
			j = 0;
			while (cur->files[j])
				printf("*** %s\n", cur->files[j++]);
		}
		while (cur)
		{
			printf("%d --- %s %d\n", i, cur->content, cur->type);
			cur = cur->next;
		}
		printf("cmd pipex = %s\n", get_cmd_pipex(tokens[i++]));
	}
	return (tokens);
}
