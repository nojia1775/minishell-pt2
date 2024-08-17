/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:46:16 by almichel          #+#    #+#             */
/*   Updated: 2024/08/17 14:45:18 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_global(t_global *global)
{
	global->data = (t_data *)malloc(sizeof(t_data));
	if (!global->data)
		return (0);
	global->pipes = (t_pipes *)malloc(sizeof(t_pipes));
	if (!global->pipes)
		return (free(global->data), 0);
	global->cur = NULL;
	global->data->code = 0;
	global->exp_var = NULL;
	global->env = NULL;
	global->data->path = NULL;
	global->data->str = NULL;
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
	}
	else if (global->cur->nbr_pipe > 0)
	{
		//sv = dup(STDIN_FILENO);
		global->envv = stock_total_env(&global->env, &global->exp_var);
		main_pipes(global);
		//dup2(sv, STDOUT_FILENO);
	}
	free_all(global);
}

int	main(int ac, char **argv, char **envp)
{
	t_global	global;
	int		pars_error;
	
	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalHandler);
	(void)ac;
	(void)argv;
	while (1)
	{
		if (!init_global(&global))
			return (9);
		stock_env(envp, &global.env);
		global.data->envp = envp;
		global.data->pwd = getcwd(global.data->buf, sizeof(global.data->buf));
		global.data->total_setup = init_lobby(global.data);
		if (set_interactive_signals() == -1)
			exit(1);
		global.data->str = readline(global.data->total_setup);
		if (global.data->str == NULL)
		{
			free_all(&global);
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
	//	printf("exit code is %lld\n",  data.code);
	}
	exit(global.data->code);
}
