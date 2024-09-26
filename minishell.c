/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:46:16 by almichel          #+#    #+#             */
/*   Updated: 2024/09/26 14:49:04 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_global(t_global *global, t_data *data)
{
	global->pipes = (t_pipes *)malloc(sizeof(t_pipes));
	if (!global->pipes)
		return (0);
	global->cur = NULL;
	data->str = NULL;
	global->tokens = NULL;
	global->data = data;
	return (1);
}

static void	routine(t_global *global)
{
	global->cur = *(global->tokens);
	if (global->cur->nbr_pipe == 0)
	{
		if (setup_exe_simple_cmd(global->cur, global) == -1)
			exit(127);
	}
	else if (global->cur->nbr_pipe > 0)
	{
		global->data->envv = stock_total_env(&global->data->env,
				&global->data->exp_var);
		main_pipes(global);
		free_reset_global(global);
	}
}

static void	execution(t_global *global)
{
	if (global->tokens)
		routine(global);
	else
		free_reset_global(global);
}

static int	loop(t_data *data, t_global *global)
{
	int	pars_error;

	while (1)
	{
		data->total_setup = init_lobby_r(data);
		if (!init_global(global, data))
			return (free_all(global), 9);
		if (set_interactive_signals() == -1)
			exit(1);
		global->data->str = readline(global->data->total_setup);
		if (global->data->str == NULL)
		{
			free_all(global);
			printf("exit\n");
			exit (0);
		}
		else
			add_history(global->data->str);
		global->tokens = parsing_pt2(global->data->str, global, &pars_error);
		if (pars_error)
			return (printf("ERROR PARSING\n"));
		execution(global);
	}
	return (0);
}

int	main(int ac, char **argv, char **envp)
{
	t_global	global;
	t_data		data;
	int			r;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	(void)ac;
	(void)argv;
	data.envp = envp;
	data.pwd = getcwd(data.buf, sizeof(data.buf));
	data.env = NULL;
	data.envv = NULL;
	data.exp_var = NULL;
	stock_env(envp, &data.env);
	r = loop(&data, &global);
	if (r)
		return (r);
	exit(127);
}
