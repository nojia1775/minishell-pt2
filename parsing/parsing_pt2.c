/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:13:22 by noah              #+#    #+#             */
/*   Updated: 2024/09/06 18:01:28 by nadjemia         ###   ########.fr       */
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
	int		i;
	char	opp;

	i = 0;
	if (redir == '<')
		opp = '>';
	else if (redir == '>')
		opp = '<';
	if (input[1] == input[0])
		i++;
	if (!input[i + 1])
		return (0);
	if (!loop_confirm_redir(input, redir, opp, &i))
		return (0);
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
	tmp = ft_strtrim(input, "\t \v\r\b");
	if (tmp[0] == '\0')
		return (free(tmp), NULL);
	if (full_whitespace(tmp))
		return (free(tmp), printf("full whitespace\n"), NULL);
	if (!nbr_quotes(tmp))
		return (free(tmp), print_error(0), NULL);
	if (!conform_pipe(tmp))
		return (free(tmp), print_error(2), NULL);
	if (!conform_redir(tmp))
		return (free(tmp), print_error(1), NULL);
	free(input);
	tokens = tokenisation(tmp, global, error_flag);
	return (tokens);
}
