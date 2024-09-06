/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:50:01 by nadjemia          #+#    #+#             */
/*   Updated: 2024/09/06 17:48:58 by nadjemia         ###   ########.fr       */
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

static int	already_a_cmd(t_token *cur, char **cmd, int flag)
{
	while (cur)
	{
		if (flag)
		{
			if (cur->type == ARG || cur->type == OPT)
			{
				if (!concat(cur, cmd))
					return (0);
			}
			else if (*cmd[0] != '\0')
				break ;
		}
		else
		{
			if (cur->type == ARG || cur->type == OPT || cur->type == CMD)
			{
				if (!concat(cur, cmd))
					return (0);
			}
			else if (*cmd[0] != '\0')
				break ;
		}
		cur = cur->next;
	}
	return (1);
}

static char	*join(t_token *line)
{
	t_token	*cur;
	char	*cmd;
	int		flag;

	flag = 0;
	cur = line;
	if (is_redir(cur))
	{
		cmd = ft_strjoin(get_cmd(cur), "\r");
		flag = 1;
	}
	else
		cmd = ft_strdup("");
	if (!cmd)
		return (NULL);
	if (!already_a_cmd(cur, &cmd, flag))
		return (NULL);
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
