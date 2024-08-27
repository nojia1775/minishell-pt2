/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:25:05 by nadjemia          #+#    #+#             */
/*   Updated: 2024/08/27 18:25:35 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Check la redirection et agit agit en consequences
int	check_redirection(t_token *cur, int *fd, t_data *data)
{
	int i;
	int fd2;

	fd2 = -1;
	i = 0;

	cur->flag = 0;

	if (cur->redir)
	{
		while (cur->redir[i])
		{
			if (ft_strcmp(">>", cur->redir[i]) == 0)
			{
				*fd = open(cur->files[i], O_WRONLY | O_APPEND, 0644);
				if (access(cur->files[i], W_OK) == -1 && access(cur->files[i], F_OK) == 0)
				{
					ft_putstr_msg(": Permission denied\n", 2, cur->files[i]);
					data->code = 1;
					return (-1);
				}
				else 
				{
					*fd = open(cur->files[i], O_WRONLY | O_CREAT | O_APPEND, 0777);
					if (access(cur->files[i], R_OK) != 0)
					{
						ft_putstr_msg(": Permission denied\n", 2, cur->files[i]);
						data->code = 1;
						return (-1);
					}
					cur->flag = 1;
					data->code = 0;
				}
			}
			else if (ft_strcmp(">", cur->redir[i]) == 0)
			{
				*fd = open(cur->files[i], O_WRONLY | O_TRUNC, 0644);
				if (access(cur->files[i], W_OK) == -1 && access(cur->files[i], F_OK) == 0)
				{
					ft_putstr_msg(": Permission denied\n", 2, cur->files[i]);
					data->code = 1;
					return (-1);
				}
				else
				{
					*fd = open(cur->files[i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
					if (access(cur->files[i], R_OK) != 0)
					{
						data->code = 1;
						ft_putstr_msg(": Permission denied\n", 2, cur->files[i]);
						return (-1);
					}
					cur->flag = 1;
					data->code = 0;
				}
			}
			else if (ft_strcmp("<", cur->redir[i]) == 0)
			{
				if (access(cur->files[i], F_OK) != 0)
				{
					ft_putstr_msg(": No such file or directory\n", 2, cur->files[i]);
					data->code = 1;
					return (-1);
				}
				else
				{
					*fd = open(cur->files[i], O_RDONLY);
					if (access(cur->files[i], R_OK) != 0)
					{
						ft_putstr_msg(": Permission denied\n", 2, cur->files[i]);
						data->code = 1;
						return (-1);
					}
					cur->flag = 1;
					data->code = 0;
				}
			}
			else if (ft_strcmp("<<", cur->redir[i]) == 0)
			{        
				here_doc(cur->files[i], cur);
				fd2 = open(cur->here_file, O_RDONLY);
			//	cur->flag = 1;
				if(dup2(fd2, STDIN_FILENO) == -1)
					perror("dup2");
				close(fd2);
				//unlink(cur->here_file);
				//return (0);
			}
			i++;
		}
	}
	return (0);
}

