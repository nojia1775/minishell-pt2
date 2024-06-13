/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:48:58 by almichel          #+#    #+#             */
/*   Updated: 2024/05/13 15:50:09 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	sigint_received;

// Ca c'est ce qui permet de faire un retour a la ligne a chaque ctrl C et quitte le programme quand tu ctrl D
void	signalHandler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	sigint_received = 1;
}

int	set_interactive_signals(void)
{
	sigint_received  = 0;
	if (signal(SIGINT, signalHandler) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	return (1);

}
void	sig_exec_handler(int signum)
{
	sigint_received = signum;
	if (signum == SIGQUIT)
		write(2, "Quit (core dumped)", 19);
	write(2, "\n", 1);
}

/*Signals detection when a command process is running*/
int	set_exec_signals(t_code *code)
{
	sigint_received = 0;
	if (signal(SIGINT, sig_exec_handler) == SIG_ERR)
	{
		code->code = 131;
		perror("signal");
		return (-1);
	}
	if (signal(SIGQUIT, sig_exec_handler) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	return (1);
}
