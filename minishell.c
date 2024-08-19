/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:46:16 by almichel          #+#    #+#             */
/*   Updated: 2024/08/19 10:25:27 by codespace        ###   ########.fr       */
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
	global->data = data;
	return (1);
}

static void	routine(t_global *global)
{
	int	sv;
	
	global->cur = *(global->tokens);
	if (global->cur->nbr_pipe == 0)
	{
		sv = dup(STDIN_FILENO);
		if (setup_exe_simple_cmd(global->cur, global) == -1)
			exit(global->data->code);
		dup2(sv, STDOUT_FILENO);
		free_reset_global(global);
	}
	else if (global->cur->nbr_pipe > 0)
	{
		//sv = dup(STDIN_FILENO);
		global->data->envv = stock_total_env(&global->data->env,
			&global->data->exp_var);
		main_pipes(global);
		//dup2(sv, STDOUT_FILENO);
		free_reset_global(global);
	}
}

int	main(int ac, char **argv, char **envp)
{
	t_global	global;
	t_data		data;
	int		pars_error;
	
	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalHandler);
	(void)ac;
	(void)argv;
	data.envp = envp;
	data.pwd = getcwd(data.buf, sizeof(data.buf));
	data.env = NULL;
	data.envv = NULL;
	data.exp_var = NULL;
	stock_env(envp, &data.env);
	while (1)
	{
		data.total_setup = init_lobby(&data);
		if (!init_global(&global, &data))
			return (free_all(&global), 9);
		if (set_interactive_signals() == -1)
			exit(1);
		global.data->str = readline(global.data->total_setup);
		if (global.data->str == NULL)
		{
			free_reset_global(&global);
			printf("exit\n");
			exit (1);
		}
		else
			add_history(global.data->str);
		global.tokens = parsing_pt2(global.data->str, &global, &pars_error);
		if (pars_error)
			return (printf("ERROR PARSING\n"));
		if (global.tokens)
			routine(&global);
		//free_reset_global(&global);
	}
	exit(global.data->code);
}
