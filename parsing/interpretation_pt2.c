/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretation_pt2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:53:48 by noah              #+#    #+#             */
/*   Updated: 2024/09/25 15:55:44 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	arg_redir(char *str)
{
	if (!ft_strcmp(str, ">>") || !ft_strcmp(str, ">")
		|| !ft_strcmp(str, "<"))
		return (1);
	return (0);
}

// remplace les variables d'environnement par leur valeur
static void	replace(t_token *tokens, t_list **env, t_list **exp_var,
	t_vars_6 *vars)
{
	vars->value = get_env_value(tokens->content
			+ vars->i, env, exp_var, *(vars->code));
	if (vars->value != NULL)
	{
		ft_strlcpy(&vars->buffer[vars->ibuf], vars->value,
			ft_strlen(vars->value) + 1);
		vars->ibuf += ft_strlen(vars->value);
		vars->i += word_len(tokens->content + vars->i);
		free(vars->value);
	}
	else
		vars->i += word_len(tokens->content + vars->i);
	if (arg_redir(vars->buffer))
		tokens->type = ARG;
}

// cherche et remplace les variables d'environnement par leur valeur
static void	search_replace(t_token *tokens, t_global *global)
{
	t_vars_6	vars;

	ft_memset(&vars, 0, sizeof(vars));
	vars.code = &global->data->code;
	ft_bzero(vars.buffer, sizeof(vars.buffer));
	while (tokens->content[vars.i])
	{
		is_in_quote(&vars.in_single, &vars.in_double,
			tokens->content[vars.i]);
		if (tokens->content[vars.i] == '$' && !vars.in_single
			&& (tokens->content[vars.i + 1] != '$'
				&& tokens->content[vars.i + 1] != '\0'
				&& tokens->content[vars.i + 1] != ' ')
			&& tokens->content[vars.i + 1] != '"')
			replace(tokens, &global->data->env, &global->data->exp_var, &vars);
		else
			vars.buffer[vars.ibuf++] = tokens->content[vars.i++];
	}
	free(tokens->content);
	if (ft_strlen(vars.buffer))
		tokens->content = ft_strdup(vars.buffer);
	else
		tokens->content = NULL;
}

// expand les variables d'environnement
void	expand(t_token **tokens, t_global *global)
{
	t_token	*cur;
	int		i;

	i = -1;
	while (tokens[++i])
	{
		cur = tokens[i];
		while (cur)
		{
			if (!cur->prev)
				search_replace(cur, global);
			else if (!cur->prev->content || ft_strcmp(cur->prev->content, "<<"))
				search_replace(cur, global);
			cur = cur->next;
		}
	}
}
