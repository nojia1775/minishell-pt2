/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intrerpretation_pt2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:53:48 by noah              #+#    #+#             */
/*   Updated: 2024/06/13 18:32:40 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_var
{
	char	buffer[1000];
	char	*value;
	int		i;
	int		ibuf;
	int		in_single;
	int		in_double;
}		t_var;

// remplace les variables d'environnement par leur valeur
static void	replace(t_token *tokens, t_list **env, t_list **exp_var, t_var *vars)
{
	vars->value = get_env_value(tokens->content + vars->i, env, exp_var);
	if (vars->value)
	{
		ft_strlcpy(&vars->buffer[vars->ibuf], vars->value, 
			ft_strlen(vars->value) + 1);
		vars->ibuf += ft_strlen(vars->value);
		vars->i += word_len(tokens->content + vars->i);
	}
	else
		vars->i += word_len(tokens->content + vars->i);
}

// cherche et remplace les variables d'environnement par leur valeur
static void	search_replace(t_token *tokens, t_list **env, t_list **exp_var)
{
	t_var	vars;
	
	vars.in_double = 0;
	vars.in_single = 0;
	vars.ibuf = 0;
	vars.i = 0;
	ft_bzero(vars.buffer, sizeof(vars.buffer));
	while (tokens->content[vars.i])
	{
		is_in_quote(&vars.in_single, &vars.in_double, 
			tokens->content[vars.i]);
		if (tokens->content[vars.i] == '$' && !vars.in_single)
			replace(tokens, env, exp_var, &vars);
		else
			vars.buffer[vars.ibuf++] = tokens->content[vars.i++];
	}
	free(tokens->content);
	tokens->content = ft_strdup(vars.buffer);
}

// expand les variables d'environnement
void	expand(t_token **tokens, t_list **env, t_list **exp_var)
{
	t_token	*cur;
	int		i;
	
	i = -1;
	while (tokens[++i])
	{
		cur = tokens[i];
		while (cur)
		{
			if (cur->type != LIM)
				search_replace(cur, env, exp_var);
			cur = cur->next;
		}
	}
}