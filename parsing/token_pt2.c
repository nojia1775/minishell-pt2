/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pt2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:19:32 by noah              #+#    #+#             */
/*   Updated: 2024/06/04 13:29:04 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*cur;
	t_token	*rm;
	int		i;
		
	i = 0;
	cur = tokens[i];
	while (tokens[i])
	{
		while (cur)
		{
			rm = cur;
			free(cur->content);
			cur = cur->next;
			free(rm);
		}
		i++;
	}
	free(tokens);
}

int	add_token(t_token **tokens, char *content)
{
	t_token	*cur;
	t_token	*new;

	if (!content[0])
		return (0);
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->content = ft_strdup(content);
	new->next = NULL;
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

static void	split_tokens(char *str, t_token **tokens)
{
	int		in_single;
	int		in_double;
	int		ibuf;
	int		i;
	int		pipe;
	char	buffer[100];
	
	ft_bzero(buffer, sizeof(buffer));
	in_single = 0;
	in_double = 0;
	ibuf = 0;
	i = -1;
	pipe = 0;
	while (str[++i])
	{
		is_in_quote(&in_single, &in_double, str[i]);
		if (str[i] == ' ' && !in_double && !in_single)
		{
			add_token(&tokens[pipe], buffer);
			ft_bzero(buffer, sizeof(buffer));
			ibuf = 0;
		}
		else if (str[i] != '"' && str[i] != '\'')
			buffer[ibuf++] = str[i];
	}
}

t_token	**tokenisation(char *str, t_list **env, t_list **exp_var)
{
	t_token	**tokens;

	(void)env;
	(void)exp_var;
	tokens = (t_token **)malloc(sizeof(t_token *));
	if (!tokens)
		return (NULL);
	tokens[0] = NULL;
	split_tokens(str, tokens);
	return (tokens);
}