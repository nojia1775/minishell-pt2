/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:46:13 by nadjemia          #+#    #+#             */
/*   Updated: 2024/07/16 14:19:36 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct	s_vars
{
	t_data	**data;
	t_list	**env;
	t_list	**expv;
}		t_vars;


static int	builtins(t_token *input, t_vars *vars)
{
	char	*tmp;
	
	if (!ft_strcmp(input->content, "exit"))
	{
		ft_exit(vars->data, vars->env, vars->expv);
		exit(vars->data[0]->code);
	}
	else if (!ft_strcmp(input->content, "env"))
		print_env(vars->env, vars->expv, vars->data);
	else if (!ft_strcmp(input->content, "pwd"))
		print_pwd(tmp, vars->data);
}

void	exec(t_token **input, t_data **data, t_list **env, t_list **expv)
{
	t_token *cur;
	int		pipe;
	t_vars	*vars;

	vars->data = data;
	vars->env = env;
	vars->expv = expv;
	pipe = 0;
	while (input[pipe])
	{
		cur = input[pipe];
		while (cur)
		{
			if (cur->type == CMD)
				if (is_a_builtin(cur->content))
					builtins(cur, vars);
		}
	}
}
