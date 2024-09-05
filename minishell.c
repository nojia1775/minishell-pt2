/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:46:16 by almichel          #+#    #+#             */
/*   Updated: 2024/09/05 12:11:06 by noah             ###   ########.fr       */
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
	int i = 0;
	while (global->cur->cmd_pipex[i])
		printf("--- %s\n", global->cur->cmd_pipex[i++]);
	i = 0;
	if (global->cur->redir)
	{
		while (global->cur->redir[i])
		{
			printf("\tredir = %s\n", global->cur->redir[i]);
			if (global->cur->files[i])
				printf("\tfiles = %s\n", global->cur->files[i]);
			i++;
		}
	}
	t_token *tmp = global->cur;
	while (tmp)
	{
		printf("+++ %s %d\n", tmp->content, tmp->type);
		tmp = tmp->next;
	}
	if (global->cur->nbr_pipe == 0)
	{
		sv = dup(STDIN_FILENO);
		if (setup_exe_simple_cmd(global->cur, global) == -1)
			exit(global->data->code);
		dup2(sv, STDOUT_FILENO);
		// free_reset_global(global);
	}
	else if (global->cur->nbr_pipe > 0)
	{
		global->data->envv = stock_total_env(&global->data->env,
				&global->data->exp_var);
		main_pipes(global);
		free_reset_global(global);
	}
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
			printf("exit\n");
			exit (1);
		}
		else
			add_history(global->data->str);
		global->tokens = parsing_pt2(global->data->str, global, &pars_error);
		if (pars_error)
			return (printf("ERROR PARSING\n"));
		if (global->tokens)
			routine(global);
		else
			free_reset_global(global);
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
	exit(global.data->code);
}
