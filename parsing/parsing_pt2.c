/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:13:22 by noah              #+#    #+#             */
/*   Updated: 2024/08/17 14:04:54 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(int error)
{
	char	*msg[2];
	
	msg[0] = "minishell: syntax error";
	msg[1] = "minishell: syntax error near unexpected token `newline'";
	printf("%s\n", msg[error]);
}

static int	full_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\v'
		|| str[i] == '\t' || str[i] == '\f' || str[i] == '\b')
	{
		if (str[i] == '\0')
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

t_token	**parsing_pt2(char *input, t_global *global, int *error_flag)
{
	t_token	**tokens;

	*error_flag = 0;
	if (input[0] == '\0')
		return (NULL);
	if (full_whitespace(input))
		return (NULL);
	if (!nbr_quotes(input))
		return (print_error(0), NULL);
	if (!conform_pipe(input))
		return (print_error(0), NULL);
	tokens = tokenisation(input, global, error_flag);
	/*if (error(tokens))
		return (NULL);*/
	// int i = 0;
	// t_token *cur;
	// while (tokens[i])
	// {
	// 	cur = tokens[i];
	// 	if (cur->redir)
	// 	{
	// 		int k = -1;
	// 		while (cur->redir[++k] && cur->files[k])
	// 			printf("redir = %s | files = %s\n", cur->redir[k], cur->files[k]);
	// 	}
	// 	while (cur)
	// 	{
	// 		printf("%s | type = %d\n", cur->content, cur->type);
	// 		cur = cur->next;
	// 	}
	// 	printf("\n");
	// 	int j = 0;
	// 	if (tokens[i]->redir)
	// 	{
	// 		while (tokens[i]->redir[j])
	// 		{
	// 			printf("redir = %s | files = %s\n", tokens[i]->redir[j], tokens[i]->files[j]);
	// 			j++;
	// 		}	
	// 	}
	// 	else
	// 		printf("NO REDIR\n");
	// 	i++;
	// }
	return (tokens);
}
