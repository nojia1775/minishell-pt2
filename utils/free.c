/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 23:05:39 by noah              #+#    #+#             */
/*   Updated: 2024/09/26 09:17:22 by nadjemia         ###   ########.fr       */
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
	free(token->redir);
	i = 0;
	if (token->files)
		while (token->files[i])
			free(token->files[i++]);
	free(token->files);
}

void	free_all(t_global *global)
{
	if (global->tokens)
		free_tokens(global->tokens);
	global->tokens = NULL;
	if (global->data)
	{
		ft_free_lists(global->data->env, global->data->exp_var);
		if (global->data->total_setup)
			free(global->data->total_setup);
	}
	if (global->pipes)
		free(global->pipes);
}

void	free_tokens(t_token **tokens)
{
	t_token	*cur;
	int		i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		cur = tokens[i];
		free_redir_files(cur);
		rm_token(cur);
		i++;
	}
	free(tokens);
	tokens = NULL;
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

void	free_reset_global(t_global *global)
{
	int	i;

	i = 0;
	if (global->tokens)
		free_tokens(global->tokens);
	global->tokens = NULL;
	if (global->pipes)
		free(global->pipes);
	global->pipes = NULL;
	if (global->data)
	{
		if (global->data->total_setup)
		{
			free(global->data->total_setup);
			global->data->total_setup = NULL;
		}
		if (global->data->envv)
		{
			while (global->data->envv[i])
				free(global->data->envv[i++]);
			free(global->data->envv);
			global->data->envv = NULL;
		}
	}
}
