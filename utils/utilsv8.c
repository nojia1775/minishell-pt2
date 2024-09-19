/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsv8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:06:56 by noah              #+#    #+#             */
/*   Updated: 2024/09/19 14:19:11 by nadjemia         ###   ########.fr       */
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

static t_token	*init_new_token(char *content, int nbr_pipe)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->nbr_pipe = nbr_pipe;
	new->next = NULL;
	new->redir = NULL;
	new->files = NULL;
	new->here_file = NULL;
	new->cmd_pipex = NULL;
	new->fd_out = -1;
	new->fd = -1;
	new->type = -1;
	return (new);
}

// ajoute un token à la liste chainée
int	add_token(t_token **tokens, char *content, int nbr_pipe)
{
	t_token	*cur;
	t_token	*new;

	if (!content[0])
		return (1);
	new = init_new_token(content, nbr_pipe);
	if (!new)
		return (0);
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
