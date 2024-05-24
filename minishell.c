/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:46:16 by almichel          #+#    #+#             */
/*   Updated: 2024/05/24 04:02:12 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **argv, char **envp)
{
	t_list	*env;
	t_data	data;
	t_list	*exp_var;
	t_code	code;

	code.code = 0;
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
		parsing(&data.str, &env, &exp_var);
		printf("%s\n", data.str);
		if (data.str != NULL)
			add_history(data.str);
		if (data.str == NULL)
		{
			ft_printf("exit\n");
			exit (code.code);
		}
		if (strcmp("env", data.str) == 0)
		{
			print_env(&env, &exp_var);
		}
		else if (strncmp("pwd", data.str, 3) == 0)
		{
			print_pwd(data.str, &code);
		}
		else if (strncmp("exit", data.str, 4) == 0)
		{
			ft_exit(data.str, &env, &exp_var, &code);
			exit(code.code);
		}
		else if (strncmp("cd ~", data.str, 4) == 0)
		{
			ft_cd_home(&data, &env);
		}
		else if (strncmp("cd", data.str, 2) == 0)
		{
			ft_cd(&data, &env, &exp_var, &code);
		}
		else if (strncmp("export", data.str, 6) == 0)
			pars_export(data.str, &env, &exp_var, &data, &code);
		else if (strncmp("unset", data.str, 5) == 0)
			pars_unset(data.str, &env, &exp_var, &code);
		else if (strncmp("ls", data.str, 2) == 0)
			setup_exe_simple_cmd(data.str, &env, &exp_var, "test", ">>", &code);
		else if (ft_strncmp(data.str, "wc", 2) == 0)
		{
			char 	**envv = stock_total_env(&env, &exp_var);
			main_pipes(ft_count_words(data.str, ' ') + 1, ft_split(data.str, ' '), envv, &code, data.str);
		}
		else if (strncmp("here", data.str, 4) == 0)
			here_doc(data.str);
	}
	exit(code.code);
}
