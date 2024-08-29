/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:50:01 by nadjemia          #+#    #+#             */
/*   Updated: 2024/08/29 13:08:36 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	concat(t_token *cur, char **cmd)
{
	char	*tmp;

	tmp = *cmd;
	*cmd = ft_strjoin(*cmd, cur->content);
	if (!cur)
		return (free(tmp), 0);
	free(tmp);
	tmp = *cmd;
	*cmd = ft_strjoin(*cmd, "\r");
	if (!cur)
		return (free(tmp), 0);
	free(tmp);
	return (1);
}

static char	*join(t_token *line)
{
	t_token	*cur;
	char	*cmd;

	cur = line;
	cmd = ft_strdup("");
	if (!cmd)
		return (NULL);
	while (cur)
	{
		if (cur->type == CMD || cur->type == ARG || cur->type == OPT)
		{
			if (!concat(cur, &cmd))
				return (NULL);
		}
		else if (cmd[0] != '\0')
			break ;
		cur = cur->next;
	}
	return (cmd);
}

void	create_cmd_pipex(t_token **tokens)
{
	int		pipe;
	char	*tmp;

	pipe = 0;
	while (tokens[pipe])
	{
		tmp = join(tokens[pipe]);
		tokens[pipe]->cmd_pipex = ft_split(tmp, '\r');
		free(tmp);
		pipe++;
	}
}

char	**get_cmd_pipex(t_token *line)
{
	t_token	*cur;

	cur = line;
	while (cur->prev)
		cur = cur->prev;
	return (cur->cmd_pipex);
}
