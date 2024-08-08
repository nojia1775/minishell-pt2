/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:13:22 by noah              #+#    #+#             */
/*   Updated: 2024/08/08 17:36:55 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	**parsing_pt2(char *input, t_list **env, t_list **exp_var, long long *code)
{
	t_token	**tokens;
	//t_token	*cur;
	
	if (input[0] == '\0')
		return (NULL);
	if (!nbr_quotes(input))
		return (printf("minishell : syntax error\n"), NULL);
	if (!conform_redir(input))
		return (printf("minishell : syntax error near unexpected token `>'\n"), NULL);
	if (!conform_pipe(input))
		return (printf("minishell : Syntax error\n"), NULL);
	tokens = tokenisation(input, env, exp_var, code);
	if (!tokens)
		return (NULL);
	/*int i = 0;
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
			if (cur->content)
				printf("%d --- %s %d\n", i, cur->content, cur->type);
			else
				printf("NULL\n");
			cur = cur->next;
		}
		int k = 0;
		while (tokens[i]->cmd_pipex[k])
			printf("cmd pipex = %s\n", tokens[i]->cmd_pipex[k++]);
		i++;
	}*/
	return (tokens);
}
