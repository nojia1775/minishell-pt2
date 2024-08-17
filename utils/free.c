/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 23:05:39 by noah              #+#    #+#             */
/*   Updated: 2024/08/17 14:41:09 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_redir_files(t_token *token)
{
	int	i;

	i = 0;
	if (token->redir)
		while (token->redir[i])
			free(token->redir[i++]);
	i = 0;
	if (token->files)
		while (token->files[i])
			free(token->files[i++]);
}

void	free_all(t_global *global)
{
	if (global->tokens)
		free_tokens(global->tokens);
	ft_free_lists(&global->env, &global->exp_var);
	if (global->data)
	{
		if (global->data->total_setup)
			free(global->data->total_setup);
		free(global->data);
	}
	if (global->pipes)
		free(global->pipes);
}

void	free_tokens(t_token **tokens)
{
	t_token	*cur;
	t_token	*rm;
	int		i;
	int		j;
	
	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		cur = tokens[i];
		free_redir_files(cur);
		while (cur)
		{
			rm = cur;
			if (!cur->prev)
			{
				j = 0;
				while (cur->cmd_pipex[j])
					free(cur->cmd_pipex[j++]);
				free(cur->cmd_pipex);
			}
			free(cur->content);
			cur = cur->next;
			free(rm);
		}
		i++;
	}
	free(tokens);
}

void	free_double_tabs(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void	free_pipes_tokens(t_global *global)
{
	if (global->tokens)
		free_tokens(global->tokens);
	if (global->pipes)
		free(global->pipes);
}