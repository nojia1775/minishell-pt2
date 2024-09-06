/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv12.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:10:09 by nadjemia          #+#    #+#             */
/*   Updated: 2024/09/06 18:02:12 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_double_tab(char **str)
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		j = 0;
		while (str[i][j])
			j++;
		i++;
	}
	return (i);
}

char	**get_cmd_pipex(t_token *line)
{
	t_token	*cur;

	cur = line;
	while (cur->prev)
		cur = cur->prev;
	return (cur->cmd_pipex);
}

int	loop_confirm_redir(char *input, char redir, char opp, int *i)
{
	int		flag;

	flag = 0;
	while (input[++(*i)])
	{
		if (ft_isalnum(input[*i]))
			flag = 1;
		if (input[*i] == '|' && !flag)
			return (0);
		if (input[*i] == opp && !flag)
			return (0);
		if (input[*i] == redir && flag)
		{
			flag = 0;
			if (input[*i] == input[*i + 1])
				(*i)++;
		}
		else if (input[*i] == redir && !flag)
			return (0);
		if (!input[*i] && !flag)
			return (0);
	}
	return (1);
}
