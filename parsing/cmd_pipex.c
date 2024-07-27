/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:50:01 by nadjemia          #+#    #+#             */
/*   Updated: 2024/07/27 20:02:24 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*join(t_token *line)
{
	t_token	*cur;
	char	*cmd;
	char	*tmp;

	cur = line;
	cmd = ft_strdup("");
	if (!cmd)
		return (NULL);
	while (cur)
	{
		if (cur->type == CMD || cur->type == ARG || cur->type == OPT)
		{
			tmp = cmd;
			cmd = ft_strjoin(cmd, cur->content);
			if (!cur)
				return (free(tmp), NULL);
			free(tmp);
			tmp = cmd;
			cmd = ft_strjoin(cmd, " ");
			if (!cur)
				return (free(tmp), NULL);
			free(tmp);
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
		tokens[pipe]->cmd_pipex = ft_split(tmp,' ');
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