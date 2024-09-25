/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv12.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:10:09 by nadjemia          #+#    #+#             */
/*   Updated: 2024/09/25 16:26:31 by nadjemia         ###   ########.fr       */
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

static int	heredoc(t_token *cur, int i, t_global *global)
{
	char	*here_file;

	here_file = NULL;
	if (ft_strcmp(cur->redir[i], "<<") == 0)
	{
		if (here_doc(cur->files[i], &here_file) == -1)
		{
			free_reset_global(global);
			unlink(here_file);
			free(here_file);
			return (-1);
		}
		cur->fd = open(here_file, O_RDONLY);
		if (cur->fd == -1)
			return (free(here_file), -1);
		if (ft_strcmp(get_cmd(cur), "<<") && !cur->redir[i + 1]
			&& ft_strcmp(get_cmd(cur), "<"))
		{
			if (dup2(cur->fd, STDIN_FILENO) == -1)
				perror("dup2");
		}
		unlink(here_file);
		free(here_file);
	}
	return (1);
}

int	open_heredoc(t_token *cur, t_global *global, int sv, int j)
{
	int	i;

	i = 0;
	if (cur->redir)
	{
		while (cur->redir[i])
		{
			if (heredoc(cur, i, global) == -1)
				return (dup2(sv, STDIN_FILENO), -1);
			if (!global->tokens[j + 1] && !cur->redir[i + 1])
				break ;
			if (global->tokens[j + 1])
			{
				if (!thereis_heredoc(global->tokens[j + 1]))
					break ;
			}
			dup2(sv, STDIN_FILENO);
			i++;
		}
	}
	return (0);
}
