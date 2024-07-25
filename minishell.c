/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:46:16 by almichel          #+#    #+#             */
/*   Updated: 2024/07/26 00:43:46 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **argv, char **envp)
{
	t_list	*env;
	t_data	data;
	t_list	*exp_var;
	t_token	**input_tokenised;
	t_token *cur;
	
	data.code = 0;
	exp_var = NULL;
	env = NULL;
	data.path = NULL;
	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalHandler);
	ac = ac + 0;
	argv = argv + 0;
	stock_env(envp, &env);
	data.envp = envp;
	data.pwd = getcwd(data.buf, sizeof(data.buf));
	data.total_setup = init_lobby(&data);
	data.str = NULL;
	while (1)
	{
		if (set_interactive_signals() == -1)
			exit(1);
		data.str = readline(data.total_setup);
		input_tokenised = parsing_pt2(data.str, &env, &exp_var);
		if (!input_tokenised)
			continue ;
		else
			cur = *input_tokenised;
		if (data.str != NULL)
			add_history(data.str);
		if (data.str == NULL)
		{
			ft_printf("exit\n");
			exit (data.code);
		}
		else if (cur->nbr_pipe == 0)
		{
			if(setup_exe_simple_cmd(cur, &env, &exp_var, "", "", &data) == -1)
				exit(data.code);
		}
		if (ft_strncmp(data.str, "", 2) == 0)
		{
			char 	**envv = stock_total_env(&env, &exp_var);
			main_pipes(ft_count_words(data.str, ' ') + 1, ft_split(data.str, ' '), envv, &data);
		}
		else if (strncmp("here", data.str, 4) == 0)
			here_doc(data.str);
		free_tokens(input_tokenised);
	}
	exit(data.code);
}
