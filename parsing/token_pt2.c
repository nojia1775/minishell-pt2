/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pt2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:19:32 by noah              #+#    #+#             */
/*   Updated: 2024/09/25 15:57:18 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	create_token(t_vars_7 *vars, t_token **tokens, int nbr_pipe)
{
	if (!add_token(&tokens[vars->pipe], vars->buffer, nbr_pipe))
		return (0);
	ft_bzero(vars->buffer, sizeof(vars->buffer));
	vars->ibuf = 0;
	return (1);
}

// creer un token ou remplir le buffer
static int	actions(t_token **tokens, char *str, t_vars_7 *vars, int nbr_pipe)
{
	if ((str[vars->i] == ' ' || !str[vars->i] || str[vars->i] == '|')
		&& !vars->in_double && !vars->in_single)
	{
		if (!create_token(vars, tokens, nbr_pipe))
			return (0);
	}
	else if (!vars->in_double && !vars->in_single
		&& (str[vars->i] == '<' || str[vars->i] == '>')
		&& vars->i && (str[vars->i - 1] != '<'
			&& str[vars->i - 1] != '>'))
		if (!create_token(vars, tokens, nbr_pipe))
			return (0);
	if (((str[vars->i] != ' ' && str[vars->i] != '|')
			|| ((str[vars->i] == ' ' || str[vars->i] == '|')
				&& (vars->in_double || vars->in_single))) && str[vars->i])
		vars->buffer[vars->ibuf++] = str[vars->i];
	if (!vars->in_double && !vars->in_single
		&& (str[vars->i] == '>' || str[vars->i] == '<')
		&& str[vars->i + 1] != '<' && str[vars->i + 1] != '>')
		if (!create_token(vars, tokens, nbr_pipe))
			return (0);
	return (1);
}

// transforme la string recuperee dans l'input
// pour la transformer en liste chainée
static int	split_tokens(char *str, t_token **tokens, int nbr_pipe)
{
	t_vars_7	vars;

	vars.in_double = 0;
	vars.in_single = 0;
	vars.ibuf = 0;
	vars.pipe = 0;
	vars.i = -1;
	ft_bzero(vars.buffer, sizeof(vars.buffer));
	while (++vars.i < (int)ft_strlen(str) + 1)
	{
		is_in_quote(&vars.in_single, &vars.in_double, str[vars.i]);
		if (!actions(tokens, str, &vars, nbr_pipe))
			return (0);
		if (str[vars.i] == '|' && !vars.in_double && !vars.in_single)
			vars.pipe++;
	}
	return (1);
}

// transformation de l'input en tokens 
// (liste chainée avec le content et le type pour l 'exec)
t_token	**tokenisation(char *str, t_global *global, int *error_flag)
{
	size_t	nbr_pipe;
	t_token	**tokens;

	nbr_pipe = count_pipe(str) + 1;
	tokens = (t_token **)ft_calloc(nbr_pipe + 1, sizeof(t_token *)
			* (nbr_pipe + 1));
	if (!tokens)
		return (change_flag(error_flag), NULL);
	split_tokens(str, tokens, nbr_pipe - 1);
	free(str);
	expand(tokens, global);
	supp_token(tokens);
	if (tokens[0] == NULL)
		return (free_tokens(tokens), NULL);
	type_token(tokens);
	quotes(tokens);
	supp_token(tokens);
	if (tokens[0] == NULL)
		return (free_tokens(tokens), NULL);
	create_cmd_pipex(tokens);
	if (!files_and_redir(tokens, error_flag))
		return (free_tokens(tokens), NULL);
	return (tokens);
}
