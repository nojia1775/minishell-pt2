/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:13:22 by noah              #+#    #+#             */
/*   Updated: 2024/09/03 07:38:11 by codespace        ###   ########.fr       */
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

static int	conform_redir2(char *input, char redir)
{
	int	i;
	int	flag;
	char		opp;
	
	i = 0;
	flag = 0;
	if (redir == '<')
		opp = '>';
	else if (redir == '>')
		opp = '<';
	if (input[1] == input[0])
		i++;
	if (!input[i + 1])
		return (0);
	while (input[++i])
	{
		if (ft_isalnum(input[i]))
			flag = 1;
		if (input[i] == '|' && !flag)
			return (0);
		if (input[i] == opp && !flag)
			return (0);
		if (input[i] == redir && flag)
		{
			flag = 0;
			if (input[i] == input[i + 1])
				i++;
		}
		else if (input[i] == redir && !flag)
			return (0);
		if (!input[i] && !flag)
			return (0);
	}
	return (1);
}

static int	conform_redir(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '>')
		{
			if (!conform_redir2(&input[i], '>'))
				return (0);
		}
		else if (input[i] == '<')
		{
			if (!conform_redir2(&input[i], '<'))
				return (0);
		}
	}
	return (1);
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
	if (!conform_redir(input))
		return (print_error(1), NULL);
	tmp = ft_strtrim(input, "\t \v\r\b");
	free(input);
	tokens = tokenisation(tmp, global, error_flag);
	return (tokens);
}
