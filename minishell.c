/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:46:16 by almichel          #+#    #+#             */
/*   Updated: 2024/08/09 14:04:23 by nadjemia         ###   ########.fr       */
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
	return (1);
}

int	main(int ac, char **argv, char **envp)
{
	// t_list	*env;
	// t_data	data;
	// t_list	*exp_var;
	// t_token *cur;
	// t_token	**input_tokenised;
	t_global	global;
	
	if (!init_global(&global))
		return (9);
	int sv;
	// data->code = 0;
	// exp_var = NULL;
	// env = NULL;
	global.data->code = 0;
	global.exp_var = NULL;
	global.env = NULL;
	global.data->path = NULL;
	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalHandler);
	ac = ac + 0;
	argv = argv + 0;
	stock_env(envp, &global.env);
	global.data->envp = envp;
	global.data->pwd = getcwd(global.data->buf, sizeof(global.data->buf));
	global.data->total_setup = init_lobby(global.data);
	global.data->str = NULL;
	while (1)
	{
		if (set_interactive_signals() == -1)
			exit(1);
		global.data->str = readline(global.data->total_setup);
		parsing_pt2(global.data->str, &global);
		if (!global.tokens)
			continue ;
		else
			global.cur = *(global.tokens);
		if (global.data->str != NULL)
			add_history(global.data->str);
		if (global.data->str == NULL)
		{
			ft_printf("exit\n");
			exit (global.data->code);
		}
		else if (global.cur->nbr_pipe == 0)
		{
			sv = dup(STDIN_FILENO);
			if(setup_exe_simple_cmd(global.cur, &global) == -1)
				exit(global.data->code);
			dup2(sv, STDOUT_FILENO);
		}
		else if (global.cur->nbr_pipe > 0)
		{
			//sv = dup(STDIN_FILENO);
			global.envv = stock_total_env(&global.env, &global.exp_var);
			main_pipes(&global);
			//dup2(sv, STDOUT_FILENO);
		}
		else if (strncmp("here", global.data->str, 4) == 0)
			here_doc(global.data->str);
		free_tokens(global.tokens);
	//	printf("exit code is %lld\n",  data.code);
	}
	exit(global.data->code);
}
