/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:13:22 by noah              #+#    #+#             */
/*   Updated: 2024/09/02 14:00:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(int error)
{
	char	*msg[3];

	msg[0] = "minishell: syntax error";
	msg[1] = "minishell: syntax error near unexpected token `newline'";
	msg[2] = "minishell: syntax error near unexpected token `|'";
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
	char	*tmp;

	*error_flag = 0;
	if (input[0] == '\0')
		return (printf("input vide\n"), NULL);
	if (full_whitespace(input))
		return (printf("full whitespace\n"), NULL);
	if (!nbr_quotes(input))
		return (print_error(0), NULL);
	if (!conform_pipe(input))
		return (print_error(2), NULL);
	tmp = ft_strtrim(input, "\t \v\r\b");
	free(input);
	tokens = tokenisation(tmp, global, error_flag);
	return (tokens);
}
