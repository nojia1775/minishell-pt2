/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almichel <almichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 01:42:03 by almichel          #+#    #+#             */
/*   Updated: 2024/05/17 17:56:55 by almichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*change_str(char *str, int i, char *new_str)
{
	char *nbr;

	nbr = ft_itoa(i);
	new_str = ft_return_strcat(str, nbr, new_str);
	free(nbr);
	return (new_str);
}

//creer un fichier temporaire pour le here_doc, ajoute un suffixe en nombre si le nom existe deja
int	create_temp_file(char *str)
{
	int		i;
	char	*new_str;
	int		flag;
	char	*nbr;
	int		fd_temp;
	
	flag = 0;
	new_str = NULL;
	i = 0;
	fd_temp = 0;
	if (access(str, F_OK) != 0)
	{
		fd_temp = open(str, O_WRONLY | O_CREAT, 0666);
		return (fd_temp);
	}
	else
	{
		while (flag == 0 && i <= 2147483647)
		{
			nbr = ft_itoa(i);
			new_str = malloc((ft_strlen(str) + ft_strlen(nbr) + 1) * sizeof(char));
			free(nbr);
			new_str = change_str(str, i, new_str);
			if (access(new_str, F_OK) != 0)
			{	
				fd_temp = open(new_str, O_WRONLY | O_CREAT, 0666);
				free(new_str);
				flag = 1;
				return (fd_temp);
			}
			free(new_str);
			i++;
		}
	}
		return (-1);
}

void	here_doc(char *limit_word)
{
	char *line;
	int	fd;

	fd = -1;
	fd = create_temp_file("temp");
	if (fd == -1)
	{
		write(2, "Here doc error!\n", 17);
		return;
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break;
		if (ft_strcmp(line, limit_word) == 0)
		{
			break;
			free(line);
		}
		parse_line(fd, line);
		free(line);
	}
}

void	parse_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));  // Write the line to the file
	write(fd, "\n", 1);  // Add a newline character after the line
}