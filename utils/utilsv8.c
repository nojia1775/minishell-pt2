/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:06:56 by noah              #+#    #+#             */
/*   Updated: 2024/08/08 14:43:48 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_in_quote(int *in_single, int *in_double, char c)
{
	if (c == '"' && !(*in_single))
		*in_double = !(*in_double);
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
}

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

// free les tokens et leurs membres
void	free_tokens(t_token **tokens)
{
	t_token	*cur;
	t_token	*rm;
	int		i;
	int		j;
	
	i = 0;
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

// ajoute un token à la liste chainée
int	add_token(t_token **tokens, char *content, int nbr_pipe)
{
	t_token	*cur;
	t_token	*new;

	if (!content[0])
		return (1);
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->content = ft_strdup(content);
	new->nbr_pipe = nbr_pipe;
	new->next = NULL;
	new->redir = NULL;
	new->files = NULL;
	new->type = -1;
	cur = *tokens;
	if (!cur)
	{
		new->prev = NULL;
		*tokens = new;
	}
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new;
		new->prev = cur;
	}
	return (1);
}

char	*find_var(char *str, t_list **env, t_list **exp_var)
{
	char	**total_env;
	int		i;
	char	*value;
	char	*tmp;
	
	tmp = NULL;
	i = 0;
	total_env = stock_total_env(env, exp_var);
	while (total_env[i])
	{
		if (ft_strncmp(str, total_env[i], ft_strlen(str)) == 0)
			tmp = ft_strdup(total_env[i]);
		i++;
	}
	i = 0;
	while (total_env[i])
		free(total_env[i++]);
	free(total_env);
	if (!tmp)
		return (NULL);
	value = ft_strdup(tmp + ft_strlen_egal(str) + 1);
	free(tmp);
	return (value);
}
