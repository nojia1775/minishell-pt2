/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noah <noah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 01:42:03 by almichel          #+#    #+#             */
/*   Updated: 2024/09/05 10:54:41 by noah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*change_str(char *str, int i, char *new_str)
{
	char	*nbr;

	nbr = ft_itoa(i);
	new_str = ft_return_strcat(str, nbr, new_str);
	free(nbr);
	return (new_str);
}

typedef struct s_vars
{
	char	*new_str;
	char	*nbr;
	int		i;
	int		flag;
	int		fd_temp;
}	t_vars;

static int	create(t_vars *vars, char *str, t_token *cur)
{
	while (vars->flag == 0 && vars->i <= 2147483647)
	{
		vars->nbr = ft_itoa(vars->i);
		vars->new_str = malloc((ft_strlen(str)
					+ ft_strlen(vars->nbr) + 1) * sizeof(char));
		free(vars->nbr);
		vars->new_str = change_str(str, vars->i, vars->new_str);
		if (access(vars->new_str, F_OK) != 0)
		{
			vars->fd_temp = open(vars->new_str, O_WRONLY | O_CREAT, 0666);
			if (vars->fd_temp < 0)
				return (-1);
			cur->here_file = ft_strdup(vars->new_str);
			free(vars->new_str);
			vars->flag = 1;
			return (vars->fd_temp);
		}
		free(vars->new_str);
		vars->i++;
	}
	return (-1);
}

//creer un fichier temporaire pour le here_doc, ajoute un
// suffixe en nombre si le nom existe deja
int	create_temp_file(char *str, t_token *cur)
{
	t_vars	vars;
	int		r;

	vars.flag = 0;
	vars.new_str = NULL;
	vars.i = 0;
	vars.fd_temp = 0;
	if (access(str, F_OK) != 0)
	{
		cur->here_file = ft_strdup(str);
		vars.fd_temp = open(str, O_WRONLY | O_CREAT, 0666);
		if (vars.fd_temp < 0)
			return (-1);
		return (vars.fd_temp);
	}
	else
	{
		r = create(&vars, str, cur);
		if (r != -1)
			return (r);
	}
	return (-1);
}

int 	here_doc(char *limit_word, t_token *cur, t_global *global)
{
	char	*line;
	int		fd;

	fd = create_temp_file("temp", cur);
	if (fd == -1)
	{
		write(2, "Here doc error!\n", 17);
		return (-1);
	}
	while (1)
	{
		if (set_exec_signals(global->data) == -1)
			return (-1);
		line = readline("> ");
		if (line == NULL)
			return (close(fd), -1);
		if (ft_strcmp(line, limit_word) == 0)
		{
			free(line);
			break ;
		}
		parse_line(fd, line);
		free(line);
	}
	close(fd);
	return (0);
}

void	parse_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}
