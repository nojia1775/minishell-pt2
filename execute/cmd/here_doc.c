/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 01:42:03 by almichel          #+#    #+#             */
/*   Updated: 2024/09/25 16:20:45 by nadjemia         ###   ########.fr       */
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

static int	create(t_vars_3 *vars, char *str, char **here_file)
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
			*here_file = ft_strdup(vars->new_str);
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
int	create_temp_file(char *str, char **here_file)
{
	t_vars_3	vars;
	int			r;

	vars.flag = 0;
	vars.new_str = NULL;
	vars.i = 0;
	vars.fd_temp = 0;
	if (access(str, F_OK) != 0)
	{
		*here_file = ft_strdup(str);
		vars.fd_temp = open(str, O_WRONLY | O_CREAT, 0666);
		if (vars.fd_temp < 0)
			return (-1);
		return (vars.fd_temp);
	}
	else
	{
		r = create(&vars, str, here_file);
		if (r != -1)
			return (r);
	}
	return (-1);
}

int	here_doc(char *limit_word, char **here_file)
{
	char	*line;
	int		fd;

	fd = create_temp_file("temp", here_file);
	if (fd == -1)
		return (write(2, "Here doc error!\n", 17), -1);
	while (1)
	{
		if (set_interactive_signals_hd() == -1)
			return (close(fd), -1);
		line = readline("> ");
		if (line == NULL)
			return (close(fd), -1);
		if (ft_strcmp(line, limit_word) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}
		parse_line(fd, line);
		free(line);
		line = NULL;
	}
	close(fd);
	return (0);
}

void	parse_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}
