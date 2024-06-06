/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pt2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:19:32 by noah              #+#    #+#             */
/*   Updated: 2024/06/06 20:46:51 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// free les tokens et leurs membres
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

// ajoute un token à la liste chainée
int	add_token(t_token **tokens, char *content)
{
	t_token	*cur;
	t_token	*new;

	if (!content[0])
		return (1);
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

// transforme la string recuperee dans l'input
// pour la transformer en liste chainée
static int	split_tokens(char *str, t_token **tokens)
{
	int		in_single;
	int		in_double;
	int		ibuf;
	int		pipe;
	int		i;
	char	buffer[100];
	
	ft_bzero(buffer, sizeof(buffer));
	in_single = 0;
	in_double = 0;
	ibuf = 0;
	i = -1;
	pipe = 0;
	while (++i < (int)ft_strlen(str) + 1)
	{
		is_in_quote(&in_single, &in_double, str[i]);
		if (str[i] == '|' && !in_double && !in_single)
		{
			i++;
			pipe++;
		}
		if ((str[i] == ' ' || str[i] == '\0') && !in_double && !in_single)
		{
			if (!add_token(&tokens[pipe], buffer))
				return (0);
			ft_bzero(buffer, sizeof(buffer));
			ibuf = 0;
		}
		else
			buffer[ibuf++] = str[i];
	}
	return (1);
}

// transformation de l'input en tokens 
// (liste chainée avec le content et le type pour l 'exec)
t_token	**tokenisation(char *str, t_list **env, t_list **exp_var)
{
	t_token	**tokens;
	size_t	nbr_pipe;
	
	(void)env;
	(void)exp_var;
	nbr_pipe = count_pipe(str) + 1;
	tokens = (t_token **)ft_calloc(nbr_pipe + 1, sizeof(t_token *)
		* (nbr_pipe + 1));
	if (!tokens)
		return (NULL);
	split_tokens(str, tokens);
	return (tokens);
}