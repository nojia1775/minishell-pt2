/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv11.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:55:00 by nadjemia          #+#    #+#             */
/*   Updated: 2024/09/18 08:44:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir(t_token *cur)
{
	if (cur->type != -1)
	{
		if (cur->type == HEREDOC || cur->type == INREDIR
			|| cur->type == OUTREDIR || cur->type == INREDIRAPP)
			return (1);
	}
	else
	{
		if (!ft_strcmp(cur->content, "<") || !ft_strcmp(cur->content, ">")
			|| !ft_strcmp(cur->content, ">>")
			|| !ft_strcmp(cur->content, "<<"))
			return (1);
	}
	return (0);
}

void	init_lobby(t_data *data)
{
	data->logname = find_logname(data);
	if (!data->logname)
	{
		data->logname = malloc((5 * sizeof(char)));
		if (!data->logname)
			return ;
		ft_strlcpy(data->logname, "user", 5);
	}
	add_minishell(data);
	add_pwd(data);
	get_total_setup(data);
}

void	rm_token(t_token *cur)
{
	t_token	*rm;
	int		i;

	while (cur)
	{
		rm = cur;
		if (!cur->prev)
		{
			i = 0;
			while (cur->cmd_pipex[i])
				free(cur->cmd_pipex[i++]);
			free(cur->cmd_pipex);
		}
		free(cur->content);
		cur = cur->next;
		free(rm);
	}
}

void	change_flag(int *error)
{
	*error = 1;
}

void	ft_simple_err(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
