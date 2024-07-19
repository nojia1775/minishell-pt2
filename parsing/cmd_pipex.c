/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:50:01 by nadjemia          #+#    #+#             */
/*   Updated: 2024/07/19 14:48:05 by nadjemia         ###   ########.fr       */
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

	pipe = 0;
	while (tokens[pipe])
	{
		tokens[pipe]->cmd_pipex = join(tokens[pipe]);
		pipe++;
	}
}

char	*get_cmd_pipex(t_token *line)
{
	t_token	*cur;

	cur = line;
	while (cur->prev)
		cur = cur->prev;
	return (cur->cmd_pipex);
}