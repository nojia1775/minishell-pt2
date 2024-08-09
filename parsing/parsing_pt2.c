/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:13:22 by noah              #+#    #+#             */
/*   Updated: 2024/08/09 13:07:11 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing_pt2(char *input, t_global *global)
{
	//t_token	*cur;
	
	if (input[0] == '\0')
		return (0);
	if (!nbr_quotes(input))
		return (printf("minishell : syntax error\n"), 0);
	if (!conform_redir(input))
		return (printf("minishell : syntax error near unexpected token `>'\n"), 0);
	if (!conform_pipe(input))
		return (printf("minishell : Syntax error\n"), 0);
	global->tokens = tokenisation(input, global);
	if (!global->tokens)
		return (0);
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
	return (1);
}
